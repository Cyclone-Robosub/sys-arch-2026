#include <memory>
#include <string>
#include <sstream>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/string.hpp>
#include <cv_bridge/cv_bridge.hpp>
#include <opencv2/opencv.hpp>

#include "vision/keypoint_detector.hpp"
#include "custom_interfaces/msg/vision_observations.hpp"

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static void draw_detections(
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
public:
  KeypointNode()
  : Node("keypoint_node")
  {
        // Parameters
    this->declare_parameter<std::string>("model_path", "model.pt");
    this->declare_parameter<std::string>("video_path", "video.mp4");
    this->declare_parameter<int>("num_keypoints", 17);
    this->declare_parameter<double>("conf_threshold", 0.5);
    this->declare_parameter<double>("fps", 30.0);

    const std::string model_path = this->get_parameter("model_path").as_string();
    const std::string video_path = this->get_parameter("video_path").as_string();
    const int    num_keypoints = this->get_parameter("num_keypoints").as_int();
    const float  conf_threshold = static_cast<float>(
      this->get_parameter("conf_threshold").as_double());
    const double fps = this->get_parameter("fps").as_double();

        // Open video
    cap_.open(video_path);
    if (!cap_.isOpened()) {
      RCLCPP_ERROR(this->get_logger(),
                         "Cannot open video file: %s", video_path.c_str());
      throw std::runtime_error("Cannot open video file: " + video_path);
    }

        // Detector
    detector_ = std::make_unique<vision::KeypointDetector>(
            model_path, num_keypoints, conf_threshold);

    RCLCPP_INFO(this->get_logger(),
                    "Loaded model: %s  video: %s  kp: %d",
                    model_path.c_str(), video_path.c_str(), num_keypoints);

        // Publishers
    detections_pub_ = this->create_publisher<custom_interfaces::msg::VisionObservations>("keypoint_detections", 10);
    image_pub_ = this->create_publisher<sensor_msgs::msg::Image>("keypoint_image", 10);

        // Timer drives the processing loop
    const auto period = std::chrono::duration<double>(1.0 / fps);
    timer_ = this->create_wall_timer(period, std::bind(&KeypointNode::timer_callback, this));
  }

private:
  void timer_callback()
  {
    cv::Mat frame;
    if (!cap_.read(frame)) {
            // Loop the video
      cap_.set(cv::CAP_PROP_POS_FRAMES, 0);
      if (!cap_.read(frame)) {
        RCLCPP_WARN(this->get_logger(), "Failed to read frame, skipping.");
        return;
      }
    }

    auto dets = detector_->detect(frame);

        // Publish observations
    auto det_msg = custom_interfaces::msg::VisionObservations();
    for (const auto & det : dets) {
      det_msg.observations.push_back(det.to_ros_msg());
    }
    detections_pub_->publish(det_msg);

        // Publish annotated image
    draw_detections(frame, dets);
    auto img_msg = cv_bridge::CvImage(
            std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
    img_msg->header.stamp = this->now();
    image_pub_->publish(*img_msg);
  }

  cv::VideoCapture cap_;
  std::unique_ptr<vision::KeypointDetector> detector_;

  rclcpp::Publisher<custom_interfaces::msg::VisionObservations>::SharedPtr detections_pub_;
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr  image_pub_;
  rclcpp::TimerBase::SharedPtr timer_;
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
