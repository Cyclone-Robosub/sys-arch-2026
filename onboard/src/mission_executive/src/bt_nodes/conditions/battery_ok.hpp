#pragma once

#include <behaviortree_cpp/condition_node.h>

class BatteryOK : public BT::ConditionNode {
public:
    BatteryOK(const std::string& name, const BT::NodeConfig& config)
        : ConditionNode(name, config) {}

    static BT::PortsList providedPorts() {
        return {};  // Reads "battery_ok" directly from blackboard
    }

    BT::NodeStatus tick() override {
        bool ok = true;
        (void)config().blackboard->get("battery_ok", ok);
        return ok ? BT::NodeStatus::SUCCESS : BT::NodeStatus::FAILURE;
    }
};
