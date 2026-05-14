#include <cstdlib>
#include <string>

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include "vision/keypoint_detector.hpp"

class KeypointDetectorTest : public ::testing::Test
{
protected:
  static void SetUpTestSuite()
  {
    engine_path_ = get_env("VISION_KEYPOINT_MODEL_PATH");
    frame_ = load_test_image();
  }

  static std::string get_env(const char * var)
  {
    const char * val = std::getenv(var);
    return (val && *val) ? std::string(val) : std::string{};
  }

  static cv::Mat load_test_image()
  {
    const std::string path = get_env("VISION_KEYPOINT_IMAGE_PATH");
    return path.empty() ? cv::Mat{} : cv::imread(path, cv::IMREAD_COLOR);
  }

  static std::string engine_path_;
  static cv::Mat frame_;
  static constexpr int num_keypoints_ = 4;
};

std::string KeypointDetectorTest::engine_path_;
cv::Mat KeypointDetectorTest::frame_;

TEST_F(KeypointDetectorTest, PreprocessBuildsExpectedInputSize) {
  if (engine_path_.empty()) {
    GTEST_SKIP() << "Set VISION_KEYPOINT_MODEL_PATH to a TensorRT engine file";
  }
  if (frame_.empty()) {
    GTEST_SKIP() << "Set VISION_KEYPOINT_IMAGE_PATH to a readable image";
  }

  vision::KeypointDetector detector(engine_path_, num_keypoints_);
  const auto input = detector.preprocess(frame_);

  EXPECT_EQ(input.size(), static_cast<size_t>(1 * 3 * 640 * 640));
}

TEST_F(KeypointDetectorTest, DetectProducesValidDetections) {
  if (engine_path_.empty()) {
    GTEST_SKIP() << "Set VISION_KEYPOINT_MODEL_PATH to a TensorRT engine file";
  }
  if (frame_.empty()) {
    GTEST_SKIP() << "Set VISION_KEYPOINT_IMAGE_PATH to a readable image";
  }

  vision::KeypointDetector detector(engine_path_, num_keypoints_);
  const auto detections = detector.detect(frame_);

  for (const auto & det : detections) {
    EXPECT_EQ(det.keypoints.size(), static_cast<size_t>(num_keypoints_));
    EXPECT_GE(det.confidence, 0.0f);
    EXPECT_LE(det.confidence, 1.0f);
  }
}
