#pragma once
#include "commands/idle.hpp"

using idle = custom_interfaces::action::idle; // idk what this does but this was here before

namespace CycloneCommands {
    Idle::Idle(const std::string& name, const NodeConfig& conf, const RosNodeParams& params) {

    }
    
    static BT::PortsList providedPorts() {
        return providedBasicPorts({});
    }

    bool Idle::setGoal(Goal& goal) {
        return true;
    }

    NodeStatus onResultReceived(const WrappedResult& wr) {
        return NodeStatus::FAILURE;
    }

    void onHalt() {
        RCLCPP_INFO(logger(), "Idle interrupted buy new command");
    }
}