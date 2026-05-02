#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.hpp>
#include <opencv2/opencv.hpp>
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/synchronizer.h>

#include "vision/keypoint_detector.hpp"
#include "custom_interfaces/msg/vision_result.hpp"

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static void annotate_images(
  cv::Mat & frame,
  const std::vector<vision::Detection> & dets)
{
  for (const auto & det : dets) {
    cv::rectangle(frame,
                  cv::Point(static_cast<int>(det.x1), static_cast<int>(det.y1)),
                  cv::Point(static_cast<int>(det.x2), static_cast<int>(det.y2)),
                  cv::Scalar(0, 255, 0), 2);

    for (const auto & kp : det.keypoints) {
      if (kp.visibility > 0.5f) {
        cv::circle(frame,
                   cv::Point(static_cast<int>(kp.x), static_cast<int>(kp.y)),
                   4, cv::Scalar(0, 0, 255), -1);
      }
    }
  }
}

// ---------------------------------------------------------------------------
// Node
// ---------------------------------------------------------------------------

class KeypointNode : public rclcpp::Node
{
  using ImageMsg = sensor_msgs::msg::Image;
  using SyncPolicy = message_filters::sync_policies::ApproximateTime<ImageMsg, ImageMsg>;
  using Sync = message_filters::Synchronizer<SyncPolicy>;

public:
  KeypointNode()
  : Node("keypoint_node")
  {
    // Parameters
    this->declare_parameter<std::string>("model_path", "model.engine");
    this->declare_parameter<std::string>("video_path", "video.mp4");
    this->declare_parameter<int>("num_keypoints", 17);
    this->declare_parameter<double>("conf_threshold", 0.5);
    this->declare_parameter<std::string>("image_topic_left",  "/camera/left/image_raw");
    this->declare_parameter<std::string>("image_topic_right", "/camera/right/image_raw");
    this->declare_parameter<bool>("annotate_images", false);

    const std::string model_path      = this->get_parameter("model_path").as_string();
    const int         num_keypoints   = this->get_parameter("num_keypoints").as_int();
    const float       conf_threshold  = static_cast<float>(this->get_parameter("conf_threshold").as_double());
    const std::string topic_left      = this->get_parameter("image_topic_left").as_string();
    const std::string topic_right     = this->get_parameter("image_topic_right").as_string();
    annotate_images_                  = this->get_parameter("annotate_images").as_bool();

    detector_ = std::make_unique<vision::KeypointDetector>(
      model_path, num_keypoints, conf_threshold);

    RCLCPP_INFO(this->get_logger(),
      "Loaded model: %s  kp: %d  left: %s  right: %s",
      model_path.c_str(), num_keypoints, topic_left.c_str(), topic_right.c_str());

    // Publishers
    result_pub_ = this->create_publisher<custom_interfaces::msg::VisionResult>(
      "keypoint_result", 10);

    // Subscribers + synchronizer
    sub_left_.subscribe(this, topic_left);
    sub_right_.subscribe(this, topic_right);

    sync_ = std::make_shared<Sync>(SyncPolicy(10), sub_left_, sub_right_);
    sync_->registerCallback(&KeypointNode::sync_callback, this);
  }

private:
  void sync_callback(
    const ImageMsg::ConstSharedPtr & left_msg,
    const ImageMsg::ConstSharedPtr & right_msg)
  {
    cv::Mat frame_left  = cv_bridge::toCvCopy(left_msg,  "bgr8")->image;
    cv::Mat frame_right = cv_bridge::toCvCopy(right_msg, "bgr8")->image;

    auto dets_left  = detector_->detect(frame_left);
    auto dets_right = detector_->detect(frame_right);

    auto result = custom_interfaces::msg::VisionResult();

    for (const auto & det : dets_left)  result.obs_left.observations.push_back(det.to_ros_msg());
    for (const auto & det : dets_right) result.obs_right.observations.push_back(det.to_ros_msg());

    if (annotate_images_) {
      annotate_images(frame_left,  dets_left);
      annotate_images(frame_right, dets_right);
    }
    result.image_left  = *cv_bridge::CvImage(left_msg->header,  "bgr8", frame_left).toImageMsg();
    result.image_right = *cv_bridge::CvImage(right_msg->header, "bgr8", frame_right).toImageMsg();

    result_pub_->publish(result);
  }

  bool annotate_images_{false};
  std::unique_ptr<vision::KeypointDetector> detector_;

  message_filters::Subscriber<ImageMsg> sub_left_;
  message_filters::Subscriber<ImageMsg> sub_right_;
  std::shared_ptr<Sync> sync_;

  rclcpp::Publisher<custom_interfaces::msg::VisionResult>::SharedPtr result_pub_;
};

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<KeypointNode>());
  rclcpp::shutdown();
  return 0;
}
