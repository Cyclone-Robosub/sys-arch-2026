#include "vision/keypoint_detector.hpp"

#include <cstring>
#include <fstream>
#include <stdexcept>

#include <cuda_runtime_api.h>

namespace vision
{

namespace
{

void cuda_check(cudaError_t err, const char * op)
{
  if (err != cudaSuccess) {
    throw std::runtime_error(
      std::string("CUDA error in ") + op + ": " + cudaGetErrorString(err));
  }
}

}  // namespace

void KeypointDetector::Logger::log(Severity severity, const char * msg) noexcept
{
  (void)severity;
  (void)msg;
}

KeypointDetector::KeypointDetector(
  const std::string & engine_path,
  int num_keypoints,
  float conf_threshold)
: output_stride_(6 + num_keypoints * 3),
  num_keypoints_(num_keypoints),
  conf_threshold_(conf_threshold)
{
  std::ifstream file(engine_path, std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open engine: " + engine_path);
  }
  const std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);
  std::vector<char> engine_data(size);
  if (!file.read(engine_data.data(), size)) {
    throw std::runtime_error("Failed to read engine: " + engine_path);
  }

  runtime_.reset(nvinfer1::createInferRuntime(logger_));
  if (!runtime_) {
    throw std::runtime_error("Failed to create TensorRT runtime");
  }

  engine_.reset(runtime_->deserializeCudaEngine(engine_data.data(), size));
  if (!engine_) {
    throw std::runtime_error("Failed to deserialize engine: " + engine_path);
  }

  context_.reset(engine_->createExecutionContext());
  if (!context_) {
    throw std::runtime_error("Failed to create execution context");
  }

  const int nb = engine_->getNbIOTensors();
  for (int i = 0; i < nb; ++i) {
    const char * name = engine_->getIOTensorName(i);
    if (engine_->getTensorIOMode(name) == nvinfer1::TensorIOMode::kINPUT) {
      input_binding_ = i;
    } else {
      output_binding_ = i;
      const auto dims = engine_->getTensorShape(name);
      max_detections_ = static_cast<int>(dims.d[1]);
    }
  }

  const size_t input_bytes = 3UL * input_height_ * input_width_ * sizeof(float);
  const size_t output_bytes =
    static_cast<size_t>(max_detections_) * output_stride_ * sizeof(float);

  cuda_check(cudaMalloc(&d_input_, input_bytes), "cudaMalloc input");
  cuda_check(cudaMalloc(&d_output_, output_bytes), "cudaMalloc output");
  cuda_check(cudaStreamCreate(&stream_), "cudaStreamCreate");
}

KeypointDetector::~KeypointDetector()
{
  if (stream_) { cudaStreamDestroy(stream_); }
  if (d_input_) { cudaFree(d_input_); }
  if (d_output_) { cudaFree(d_output_); }
}

std::vector<float> KeypointDetector::preprocess(const cv::Mat & frame)
{
  cv::Mat resized;
  cv::resize(frame, resized, cv::Size(input_width_, input_height_));
  cv::cvtColor(resized, resized, cv::COLOR_BGR2RGB);
  resized.convertTo(resized, CV_32FC3, 1.0 / 255.0);

  // HWC -> CHW
  std::vector<cv::Mat> channels(3);
  cv::split(resized, channels);

  std::vector<float> input(3 * input_height_ * input_width_);
  for (int c = 0; c < 3; ++c) {
    std::memcpy(
      input.data() + static_cast<size_t>(c) * input_height_ * input_width_,
      channels[c].data,
      static_cast<size_t>(input_height_) * input_width_ * sizeof(float));
  }
  return input;
}

std::vector<Detection> KeypointDetector::postprocess(
  const std::vector<float> & output,
  int orig_width,
  int orig_height)
{
  const float scale_x = static_cast<float>(orig_width) / input_width_;
  const float scale_y = static_cast<float>(orig_height) / input_height_;

  std::vector<Detection> detections;

  for (int i = 0; i < max_detections_; ++i) {
    const float * row = output.data() + static_cast<size_t>(i) * output_stride_;
    const float conf = row[4];
    if (conf < conf_threshold_) {
      continue;
    }

    Detection det;
    det.x1 = row[0] * scale_x;
    det.y1 = row[1] * scale_y;
    det.x2 = row[2] * scale_x;
    det.y2 = row[3] * scale_y;
    det.confidence = conf;
    det.class_id = row[5];

    det.keypoints.reserve(num_keypoints_);
    for (int k = 0; k < num_keypoints_; ++k) {
      const int base = 6 + k * 3;
      Keypoint kp;
      kp.x = row[base] * scale_x;
      kp.y = row[base + 1] * scale_y;
      kp.visibility = row[base + 2];
      det.keypoints.push_back(kp);
    }
    detections.push_back(std::move(det));
  }

  return detections;
}

std::vector<Detection> KeypointDetector::detect(const cv::Mat & frame)
{
  const auto input = preprocess(frame);

  cuda_check(
    cudaMemcpyAsync(
      d_input_, input.data(),
      input.size() * sizeof(float),
      cudaMemcpyHostToDevice, stream_),
    "memcpy input H2D");

  context_->setTensorAddress(engine_->getIOTensorName(input_binding_), d_input_);
  context_->setTensorAddress(engine_->getIOTensorName(output_binding_), d_output_);
  if (!context_->enqueueV3(stream_)) {
    throw std::runtime_error("TensorRT enqueueV3 failed");
  }

  const size_t output_bytes =
    static_cast<size_t>(max_detections_) * output_stride_ * sizeof(float);
  std::vector<float> output(max_detections_ * output_stride_);

  cuda_check(
    cudaMemcpyAsync(
      output.data(), d_output_,
      output_bytes,
      cudaMemcpyDeviceToHost, stream_),
    "memcpy output D2H");

  cuda_check(cudaStreamSynchronize(stream_), "cudaStreamSynchronize");

  return postprocess(output, frame.cols, frame.rows);
}

}  // namespace vision
