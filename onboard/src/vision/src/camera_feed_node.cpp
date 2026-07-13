#include <memory>
#include <string>
#include <atomic>
#include <thread>
#include <algorithm>
#include <chrono>

#include <gst/gst.h>
#include <gst/app/gstappsink.h>

#include <opencv2/opencv.hpp>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.hpp>

// ---------------------------------------------------------------------------
// Node
// ---------------------------------------------------------------------------

class CameraFeedNode : public rclcpp::Node
{
public:
  CameraFeedNode()
  : Node("camera_feed_node"), running_(false)
  {
    this->declare_parameter<std::string>("device",      "/dev/video2");
    this->declare_parameter<std::string>("rtsp_url",    "rtsp://localhost:8554/cam");
    this->declare_parameter<std::string>("topic",       "camera/image_raw");
    this->declare_parameter<int>("width",   1920);
    this->declare_parameter<int>("height",  1080);
    this->declare_parameter<int>("fps",     30);

    device_   = this->get_parameter("device").as_string();
    rtsp_url_ = this->get_parameter("rtsp_url").as_string();
    width_    = this->get_parameter("width").as_int();
    height_   = this->get_parameter("height").as_int();
    fps_      = this->get_parameter("fps").as_int();

    auto topic = this->get_parameter("topic").as_string();
    image_pub_ = this->create_publisher<sensor_msgs::msg::Image>(topic, 10);

    is_video_file_ = is_video_file(device_);

    if (is_video_file_) {
      if (!init_video_capture()) {
        throw std::runtime_error("Failed to open video file: " + device_);
      }
      running_ = true;
      pipeline_thread_ = std::thread(&CameraFeedNode::run_video, this);
      RCLCPP_INFO(this->get_logger(),
        "CameraFeedNode started — video file: %s  topic: %s",
        device_.c_str(), topic.c_str());
    } else {
      if (!init_pipeline()) {
        throw std::runtime_error("Failed to initialise GStreamer pipeline");
      }
      running_ = true;
      pipeline_thread_ = std::thread(&CameraFeedNode::run_pipeline, this);
      RCLCPP_INFO(this->get_logger(),
        "CameraFeedNode started — device: %s  rtsp: %s  %dx%d @ %dfps",
        device_.c_str(), rtsp_url_.c_str(), width_, height_, fps_);
    }
  }

  ~CameraFeedNode()
  {
    running_ = false;
    if (pipeline_) {
      gst_element_set_state(pipeline_, GST_STATE_NULL);
    }
    if (pipeline_thread_.joinable()) {
      pipeline_thread_.join();
    }
    if (pipeline_) {
      gst_object_unref(pipeline_);
      pipeline_ = nullptr;
    }
    if (cap_.isOpened()) {
      cap_.release();
    }
  }

private:
  // Build and start the GStreamer pipeline.
  //
  // Pipeline layout:
  //   v4l2src  →  h264parse  →  tee ──┬──> queue → rtspclientsink  (stream to mediaMTX)
  //                                   └──> queue → avdec_h264 → videoconvert → appsink  (publish to ROS)
  bool init_pipeline()
  {
    GError * err = nullptr;

    // Raspberry Pi 5 has no H.264 hardware decoder, so decode in software
    // (avdec_h264) and let videoconvert hand appsink BGR directly.
    std::string pipeline_str =
      "v4l2src device=" + device_ + " ! "
      "video/x-h264,width=" + std::to_string(width_) +
        ",height=" + std::to_string(height_) +
        ",framerate=" + std::to_string(fps_) + "/1 ! "
      "h264parse ! "
      "tee name=t "
        "t. ! queue ! rtspclientsink location=" + rtsp_url_ + " "
        "t. ! queue ! avdec_h264 ! videoconvert ! "
          "video/x-raw,format=BGR ! "
          "appsink name=appsink emit-signals=false sync=false "
            "max-buffers=1 drop=true";

    RCLCPP_INFO(this->get_logger(), "Pipeline: %s", pipeline_str.c_str());

    pipeline_ = gst_parse_launch(pipeline_str.c_str(), &err);
    if (!pipeline_ || err) {
      RCLCPP_ERROR(this->get_logger(), "gst_parse_launch failed: %s",
        err ? err->message : "(unknown)");
      if (err) g_error_free(err);
      return false;
    }

    appsink_ = gst_bin_get_by_name(GST_BIN(pipeline_), "appsink");
    if (!appsink_) {
      RCLCPP_ERROR(this->get_logger(), "Could not find appsink element");
      gst_object_unref(pipeline_);
      pipeline_ = nullptr;
      return false;
    }

    GstStateChangeReturn ret = gst_element_set_state(pipeline_, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
      RCLCPP_ERROR(this->get_logger(), "Failed to set pipeline to PLAYING");
      gst_object_unref(appsink_);
      gst_object_unref(pipeline_);
      pipeline_ = nullptr;
      return false;
    }

    return true;
  }

  // Pull frames from appsink and publish them.  Runs on its own thread so it
  // never blocks the ROS executor.
  void run_pipeline()
  {
    while (running_ && rclcpp::ok()) {
      GstSample * sample = gst_app_sink_try_pull_sample(
        GST_APP_SINK(appsink_), GST_SECOND);   // 1 s timeout

      if (!sample) {
        // Timeout or EOS — check bus for errors before looping.
        check_bus();
        continue;
      }

      GstBuffer * buffer = gst_sample_get_buffer(sample);
      GstCaps   * caps   = gst_sample_get_caps(sample);

      // Extract width/height from caps in case they differ from parameters.
      GstStructure * s = gst_caps_get_structure(caps, 0);
      int w = 0, h = 0;
      gst_structure_get_int(s, "width",  &w);
      gst_structure_get_int(s, "height", &h);

      GstMapInfo map;
      if (gst_buffer_map(buffer, &map, GST_MAP_READ)) {
        // videoconvert outputs BGR; toImageMsg() copies, so wrapping is safe.
        cv::Mat frame(h, w, CV_8UC3, map.data);

        auto img_msg = cv_bridge::CvImage(
          std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
        img_msg->header.stamp = this->now();
        img_msg->header.frame_id = "camera";

        image_pub_->publish(*img_msg);

        gst_buffer_unmap(buffer, &map);
      }

      gst_sample_unref(sample);
    }
  }

  // Log any error messages sitting on the bus.
  void check_bus()
  {
    if (!pipeline_) return;
    GstBus * bus = gst_element_get_bus(pipeline_);
    GstMessage * msg = gst_bus_pop_filtered(bus,
      static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
    if (msg) {
      GError * err = nullptr;
      gchar  * dbg = nullptr;
      if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
        gst_message_parse_error(msg, &err, &dbg);
        RCLCPP_ERROR(this->get_logger(), "GStreamer error: %s\n%s",
          err->message, dbg ? dbg : "");
        g_error_free(err);
        g_free(dbg);
        running_ = false;
      } else {
        RCLCPP_INFO(this->get_logger(), "GStreamer EOS");
        running_ = false;
      }
      gst_message_unref(msg);
    }
    gst_object_unref(bus);
  }

  static bool is_video_file(const std::string & path)
  {
    static const std::vector<std::string> exts = {
      ".mp4", ".avi", ".mkv", ".mov", ".webm", ".m4v", ".flv", ".wmv"
    };
    std::string lower = path;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    for (const auto & ext : exts) {
      if (lower.size() >= ext.size() &&
          lower.compare(lower.size() - ext.size(), ext.size(), ext) == 0) {
        return true;
      }
    }
    return false;
  }

  bool init_video_capture()
  {
    cap_.open(device_);
    if (!cap_.isOpened()) {
      RCLCPP_ERROR(this->get_logger(), "Failed to open video file: %s", device_.c_str());
      return false;
    }
    double native_fps = cap_.get(cv::CAP_PROP_FPS);
    frame_delay_ms_ = static_cast<int>(1000.0 / (native_fps > 0 ? native_fps : fps_));
    RCLCPP_INFO(this->get_logger(), "Opened video file: %s  (%.1f fps, %d ms/frame)",
      device_.c_str(), native_fps, frame_delay_ms_);
    return true;
  }

  void run_video()
  {
    cv::Mat frame;
    while (running_ && rclcpp::ok()) {
      auto t0 = std::chrono::steady_clock::now();

      if (!cap_.read(frame) || frame.empty()) {
        RCLCPP_INFO(this->get_logger(), "Video file ended");
        running_ = false;
        break;
      }

      auto img_msg = cv_bridge::CvImage(
        std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
      img_msg->header.stamp = this->now();
      img_msg->header.frame_id = "camera";
      image_pub_->publish(*img_msg);

      auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - t0).count();
      auto sleep_ms = frame_delay_ms_ - static_cast<int>(elapsed);
      if (sleep_ms > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
      }
    }
  }

  // Parameters
  std::string device_;
  std::string rtsp_url_;
  int width_, height_, fps_;

  // GStreamer
  GstElement * pipeline_ = nullptr;
  GstElement * appsink_  = nullptr;

  // Video file
  bool is_video_file_ = false;
  int frame_delay_ms_;
  cv::VideoCapture cap_;

  // Threading
  std::atomic<bool> running_;
  std::thread pipeline_thread_;

  // ROS
  rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;
};

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(int argc, char ** argv)
{
  gst_init(&argc, &argv);

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CameraFeedNode>());
  rclcpp::shutdown();

  gst_deinit();
  return 0;
}
