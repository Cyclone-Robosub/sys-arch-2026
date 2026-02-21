#pragma once

#include <behaviortree_cpp/condition_node.h>
#include <geometry_msgs/msg/pose.hpp>
#include <cmath>

class AtWaypoint : public BT::ConditionNode {
public:
    AtWaypoint(const std::string& name, const BT::NodeConfig& config)
        : ConditionNode(name, config) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<double>("target_x", "Target X position"),
            BT::InputPort<double>("target_y", "Target Y position"),
            BT::InputPort<double>("target_z", "Target Z position"),
            BT::InputPort<double>("tolerance", 0.5, "Position tolerance in meters"),
        };
    }

    BT::NodeStatus tick() override {
        auto tx = getInput<double>("target_x");
        auto ty = getInput<double>("target_y");
        auto tz = getInput<double>("target_z");
        auto tol = getInput<double>("tolerance");

        if (!tx || !ty || !tz) {
            return BT::NodeStatus::FAILURE;
        }

        geometry_msgs::msg::Pose current;
        if (!config().blackboard->get("current_pose", current)) {
            return BT::NodeStatus::FAILURE;  // No position data yet
        }

        double dx = current.position.x - tx.value();
        double dy = current.position.y - ty.value();
        double dz = current.position.z - tz.value();
        double distance = std::sqrt(dx * dx + dy * dy + dz * dz);

        return (distance <= tol.value()) ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    }
};
