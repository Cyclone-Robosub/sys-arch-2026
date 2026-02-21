#pragma once

#include <behaviortree_cpp/action_node.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <mission_executive/types.hpp>

#include <string>
#include <vector>
#include <algorithm>

using namespace mission_executive;

class DetectObject : public BT::StatefulActionNode {
public:
    DetectObject(const std::string& name, const BT::NodeConfig& config)
        : StatefulActionNode(name, config) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<VisionTarget>("target", "Object type to detect"),
        };
    }

    BT::NodeStatus onStart() override {
        auto target = getInput<VisionTarget>("target");
        if (!target) {
            throw BT::RuntimeError("DetectObject: missing required 'target' input");
        }
        target_ = target.value();
        target_string_ = toString(target_);

        // Enable camera via blackboard-injected ROS node
        auto ros_node = config().blackboard->get<rclcpp::Node::SharedPtr>("ros_node");
        if (!camera_pub_) {
            camera_pub_ = ros_node->create_publisher<std_msgs::msg::Bool>(
                "camera1_command_topic", 10);
        }

        auto msg = std_msgs::msg::Bool();
        msg.data = true;
        camera_pub_->publish(msg);

        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override {
        // Read detections from blackboard (written by bt_executor_node)
        auto detections = config().blackboard->get<std::vector<std::string>>("detected_objects");

        auto it = std::find(detections.begin(), detections.end(), target_string_);
        if (it != detections.end()) {
            disableCamera();
            return BT::NodeStatus::SUCCESS;
        }

        return BT::NodeStatus::RUNNING;
    }

    void onHalted() override {
        disableCamera();
    }

private:
    void disableCamera() {
        if (camera_pub_) {
            auto msg = std_msgs::msg::Bool();
            msg.data = false;
            camera_pub_->publish(msg);
        }
    }

    VisionTarget target_;
    std::string target_string_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr camera_pub_;
};
