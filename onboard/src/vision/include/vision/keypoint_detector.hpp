#pragma once

#include <string>
#include <vector>

#include <torch/script.h>
#include <opencv2/opencv.hpp>

namespace vision
{

struct Keypoint
{
  float x;
  float y;
  float visibility;
};

struct Detection
{
  float x1, y1, x2, y2;     // bounding box (pixel coords in original frame)
  float confidence;
  float class_id;
  std::vector<Keypoint> keypoints;
};

class KeypointDetector {
public:
    // model_path   : path to a TorchScript traced model
    // num_keypoints: number of keypoints per detection
    // conf_threshold: minimum confidence to keep a detection
  KeypointDetector(
    const std::string & model_path,
    int num_keypoints,
    float conf_threshold = 0.2f);

  KeypointDetector(
    const torch::jit::script::Module & model,
    int num_keypoints,
    float conf_threshold = 0.2f);

    // Run inference on a BGR frame, return filtered detections.
  std::vector<Detection> detect(const cv::Mat & frame);

  torch::Tensor preprocess(const cv::Mat & frame);

  std::vector<Detection> postprocess(
    const torch::Tensor & output,
    int orig_width,
    int orig_height);

private:
  torch::jit::script::Module model_;
  int num_keypoints_;
  float conf_threshold_;
  int input_width_{640};
  int input_height_{640};
};

}  // namespace vision
