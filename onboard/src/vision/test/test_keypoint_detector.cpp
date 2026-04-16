#include <cstdlib>
#include <optional>
#include <string>

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <torch/script.h>

#include "vision/keypoint_detector.hpp"

class KeypointDetectorTest : public ::testing::Test {
protected:
  static void SetUpTestSuite()
  {
    const auto model_path = get_model_path();
    if (!model_path.empty()) {
      model_ = torch::jit::load(model_path);
      model_->eval();
    }

    frame_ = load_test_image();
  }

  static std::string get_model_path()
  {
    const char * path = std::getenv("VISION_KEYPOINT_MODEL_PATH");
    if (path == nullptr || std::string(path).empty()) {
      return {};
    }

    return std::string(path);
  }

  static cv::Mat load_test_image()
  {
    const char * path = std::getenv("VISION_KEYPOINT_IMAGE_PATH");
    if (path == nullptr || std::string(path).empty()) {
      return {};
    }

    return cv::imread(path, cv::IMREAD_COLOR);
  }

  static std::optional<torch::jit::script::Module> model_;
  static cv::Mat frame_;
  static constexpr int num_keypoints_ = 4;
};

std::optional<torch::jit::script::Module> KeypointDetectorTest::model_;
cv::Mat KeypointDetectorTest::frame_;

TEST_F(KeypointDetectorTest, PreprocessBuildsExpectedInputShape) {
    if (!model_) {
    GTEST_SKIP() << "Set VISION_KEYPOINT_MODEL_PATH to a real TorchScript model";
    }

    if (frame_.empty()) {
    GTEST_SKIP() << "Set VISION_KEYPOINT_IMAGE_PATH to a readable image";
    }

    vision::KeypointDetector detector(*model_, num_keypoints_);
    const auto input = detector.preprocess(frame_);

    EXPECT_EQ(input.sizes(), torch::IntArrayRef({1, 3, 640, 640}));
    EXPECT_EQ(input.dtype(), torch::kFloat32);
}

TEST_F(KeypointDetectorTest, RealModelPostprocessProducesDetections) {
    if (!model_) {
    GTEST_SKIP() << "Set VISION_KEYPOINT_MODEL_PATH to a real TorchScript model";
    }

    if (frame_.empty()) {
    GTEST_SKIP() << "Set VISION_KEYPOINT_IMAGE_PATH to a readable image";
    }

    vision::KeypointDetector detector(*model_, num_keypoints_);
    const auto input = detector.preprocess(frame_);
    std::vector<torch::jit::IValue> inputs{input};
    const auto output = model_->forward(inputs).toTensor();

    ASSERT_EQ(output.dim(), 3);
    EXPECT_EQ(output.size(0), 1);
    EXPECT_EQ(output.size(1), 300);
    EXPECT_GT(output.size(2), 6);
    EXPECT_EQ((output.size(2) - 6) % 3, 0);

    const int num_keypoints = static_cast<int>((output.size(2) - 6) / 3);
    vision::KeypointDetector postprocess_detector(*model_, num_keypoints);
    const auto detections = postprocess_detector.postprocess(output, frame_.cols, frame_.rows);

    EXPECT_LE(detections.size(), 300u);
    for (const auto & detection : detections) {
    EXPECT_EQ(detection.keypoints.size(), static_cast<size_t>(num_keypoints));
    }
}
