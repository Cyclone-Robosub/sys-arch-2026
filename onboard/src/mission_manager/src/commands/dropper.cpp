#include "commands/dropper.hpp"

using namespace CycloneCommands;
    DropperCmd::DropperCmd(const std::string &name, const NodeConfig &conf,
                                       const RosNodeParams &params) : RosActionNode(name, conf, params) {}

    PortsList DropperCmd::providedPorts() {
        return providedBasicPorts({
            InputPort<uint8_t>("dropper_id"),
            InputPort<double>("timeout")
        });
    }

    bool DropperCmd::setGoal(Goal &goal) {
        getInput("dropper_id", goal.dropper_id);
        getInput("timeout", goal.timeout);
        
        start_time = std::chrono::steady_clock::now();
        timeout_sec = goal.timeout;
        return true;
    }

    NodeStatus DropperCmd::tick() {
        NodeStatus status = RosActionNode::tick();

        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(now - start_time).count();
        if (timeout_sec > 0 && elapsed > timeout_sec) {
            RCLCPP_ERROR(logger(), "Dropper - Error: timeout");
            halt();
            return NodeStatus::FAILURE;
        }       
        return status;
    }

    NodeStatus DropperCmd::onResultReceived(const WrappedResult &result) {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }

