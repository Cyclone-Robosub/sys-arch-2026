#include "vision/keypoint_detector.hpp"

#include <stdexcept>

namespace vision {

KeypointDetector::KeypointDetector(const std::string & model_path,
                                   int num_keypoints,
                                   float conf_threshold)
: num_keypoints_(num_keypoints), conf_threshold_(conf_threshold)
{
    try {
        model_ = torch::jit::load(model_path);
        model_.eval();
    } catch (const c10::Error & e) {
        throw std::runtime_error("Failed to load model from \"" + model_path + "\": " + e.what());
    }
}

torch::Tensor KeypointDetector::preprocess(const cv::Mat & frame)
{
    cv::Mat resized;
    cv::resize(frame, resized, cv::Size(input_width_, input_height_));
    cv::cvtColor(resized, resized, cv::COLOR_BGR2RGB);
    resized.convertTo(resized, CV_32FC3, 1.0 / 255.0);

    // HWC -> NCHW
    auto tensor = torch::from_blob(
        resized.data,
        {1, input_height_, input_width_, 3},
        torch::kFloat32).clone();
    tensor = tensor.permute({0, 3, 1, 2}).contiguous();

    return tensor;
}

std::vector<Detection> KeypointDetector::postprocess(const torch::Tensor & output,
                                                     int orig_width,
                                                     int orig_height)
{
    // output shape: [1, 300, 6 + num_keypoints * 3]
    auto pred = output.squeeze(0);  // [300, 6 + num_keypoints * 3]

    const float scale_x = static_cast<float>(orig_width)  / input_width_;
    const float scale_y = static_cast<float>(orig_height) / input_height_;

    std::vector<Detection> detections;
    const int num_dets = static_cast<int>(pred.size(0));

    for (int i = 0; i < num_dets; ++i) {
        float conf = pred[i][4].item<float>();
        if (conf < conf_threshold_) {
            continue;
        }

        Detection det;
        det.x1         = pred[i][0].item<float>() * scale_x;
        det.y1         = pred[i][1].item<float>() * scale_y;
        det.x2         = pred[i][2].item<float>() * scale_x;
        det.y2         = pred[i][3].item<float>() * scale_y;
        det.confidence = conf;
        det.class_id   = pred[i][5].item<float>();

        det.keypoints.reserve(num_keypoints_);
        for (int k = 0; k < num_keypoints_; ++k) {
            const int base = 6 + k * 3;
            Keypoint kp;
            kp.x          = pred[i][base    ].item<float>() * scale_x;
            kp.y          = pred[i][base + 1].item<float>() * scale_y;
            kp.visibility = pred[i][base + 2].item<float>();
            det.keypoints.push_back(kp);
        }

        detections.push_back(std::move(det));
    }

    return detections;
}

std::vector<Detection> KeypointDetector::detect(const cv::Mat & frame)
{
    torch::NoGradGuard no_grad;
    auto input = preprocess(frame);
    std::vector<torch::jit::IValue> inputs{input};
    auto raw_output = model_.forward(inputs).toTensor();
    return postprocess(raw_output, frame.cols, frame.rows);
}

}  // namespace vision
