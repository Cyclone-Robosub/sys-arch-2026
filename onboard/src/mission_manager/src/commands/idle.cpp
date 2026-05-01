#pragma once
#include "commands/idle.hpp"

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