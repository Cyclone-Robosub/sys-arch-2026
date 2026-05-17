#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <NvInfer.h>
#include <cuda_runtime_api.h>
#include <opencv2/opencv.hpp>

#include "custom_interfaces/msg/keypoint.hpp"
#include "custom_interfaces/msg/bounding_box.hpp"
#include "custom_interfaces/msg/vision_observation.hpp"
#include "custom_interfaces/msg/vision_observations.hpp"

namespace vision
{

struct Keypoint
{
  float x;
  float y;
  float visibility;

  custom_interfaces::msg::Keypoint to_ros_msg() const
  {
    custom_interfaces::msg::Keypoint msg;
    msg.x = x;
    msg.y = y;
    msg.visibility = visibility;
    return msg;
  }
};

struct Detection
{
  float x1, y1, x2, y2;     // bounding box (pixel coords in original frame)
  float confidence;
  float class_id;
  std::vector<Keypoint> keypoints;

  inline static const std::unordered_map<int8_t, std::string> ClassNameById{
    {0, "gate"}
  };

  custom_interfaces::msg::VisionObservation to_ros_msg() const
  {
    custom_interfaces::msg::VisionObservation msg;
    msg.bounding_box.x1 = x1;
    msg.bounding_box.y1 = y1;
    msg.bounding_box.x2 = x2;
    msg.bounding_box.y2 = y2;
    msg.bounding_box.confidence = confidence;
    msg.category = ClassNameById.at(static_cast<int8_t>(class_id));
    for (const auto & kp : keypoints) {
      msg.keypoints.push_back(kp.to_ros_msg());
    }
    return msg;
  }
};

class KeypointDetector
{
public:
  // engine_path   : path to a serialized TensorRT engine (.engine)
  // num_keypoints : number of keypoints per detection
  // conf_threshold: minimum confidence to keep a detection
  KeypointDetector(
    const std::string & engine_path,
    int num_keypoints,
    float conf_threshold = 0.2f);

  ~KeypointDetector();

  // Run inference on a BGR frame, return filtered detections.
  std::vector<Detection> detect(const cv::Mat & frame);

  // Exposed for testing: returns a flat CHW float buffer (3 * H * W).
  std::vector<float> preprocess(const cv::Mat & frame);

  // Exposed for testing: parse flat output buffer (max_detections * output_stride).
  std::vector<Detection> postprocess(
    const std::vector<float> & output,
    int orig_width,
    int orig_height);

private:
  struct TrtDeleter
  {
    template<typename T>
    void operator()(T * p) const noexcept { delete p; }
  };

  class Logger : public nvinfer1::ILogger
  {
    void log(Severity severity, const char * msg) noexcept override;
  };

  Logger logger_;
  std::unique_ptr<nvinfer1::IRuntime, TrtDeleter> runtime_;
  std::unique_ptr<nvinfer1::ICudaEngine, TrtDeleter> engine_;
  std::unique_ptr<nvinfer1::IExecutionContext, TrtDeleter> context_;

  void * d_input_{nullptr};
  void * d_output_{nullptr};
  cudaStream_t stream_{nullptr};

  int input_binding_{0};
  int output_binding_{1};
  int max_detections_{300};
  int output_stride_;

  int num_keypoints_;
  float conf_threshold_;
  int input_width_{640};
  int input_height_{640};
};

}  // namespace vision
