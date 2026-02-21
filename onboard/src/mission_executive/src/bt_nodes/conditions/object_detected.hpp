#pragma once

#include <behaviortree_cpp/condition_node.h>
#include <mission_executive/types.hpp>

#include <string>
#include <vector>
#include <algorithm>

using namespace mission_executive;

class ObjectDetected : public BT::ConditionNode {
public:
    ObjectDetected(const std::string& name, const BT::NodeConfig& config)
        : ConditionNode(name, config) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<VisionTarget>("target", "Object type to check for"),
        };
    }

    BT::NodeStatus tick() override {
        auto target = getInput<VisionTarget>("target");
        if (!target) {
            return BT::NodeStatus::FAILURE;
        }

        std::string target_str = toString(target.value());

        std::vector<std::string> detections;
        if (!config().blackboard->get("detected_objects", detections)) {
            return BT::NodeStatus::FAILURE;
        }

        auto it = std::find(detections.begin(), detections.end(), target_str);
        return (it != detections.end()) ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    }
};
