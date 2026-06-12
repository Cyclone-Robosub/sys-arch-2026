#include "commands/command_alias.hpp"
#include "commands/idle.hpp"

using namespace CycloneCommands;
    IdleCmd::IdleCmd(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
        : RosActionNode(name, conf, params){}
    
    PortsList IdleCmd::providedPorts() {
        return providedBasicPorts({});
    }

    bool IdleCmd::setGoal([[maybe_unused]] Goal& goal) {
        return true;
    }

    NodeStatus IdleCmd::onResultReceived([[maybe_unused]] const WrappedResult& result) {
        return NodeStatus::FAILURE;
    }

    void IdleCmd::onHalt() {
        RCLCPP_INFO(logger(), "Idle interrupted buy new command");
    }
