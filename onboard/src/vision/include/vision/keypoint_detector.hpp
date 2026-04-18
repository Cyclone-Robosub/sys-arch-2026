#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <torch/script.h>
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
