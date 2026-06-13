#include "commands/duration_trick_client.hpp"

using namespace CycloneCommands;
    DurationTrickCmd::DurationTrickCmd(const std::string &name, const NodeConfig &conf,
                                       const RosNodeParams &params) : RosActionNode(name, conf, params) {}

    PortsList DurationTrickCmd::providedPorts() {
        return providedBasicPorts({
            InputPort<std::string>("trick"),
            InputPort<uint64_t>("duration"),
            InputPort<WaypointMask>("waypoint_mask"),
            InputPort<Pose6D>("tolerance"),
            InputPort<uint64_t>("hold_time"),
            InputPort<double>("timeout")
        });
    }

    bool DurationTrickCmd::setGoal(Goal &goal) {
        getInput("trick", goal.trick);
        getInput("duration", goal.duration);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("hold_time", goal.hold_time);
        getInput("timeout", goal.timeout);
        
        start_time = std::chrono::steady_clock::now();
        timeout_sec = goal.timeout;
        return true;
    }

    NodeStatus DurationTrickCmd::tick() {
        NodeStatus status = RosActionNode::tick();

        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(now - start_time).count();
        if (elapsed > timeout_sec) {
            RCLCPP_ERROR(logger(), "Error: timeout");
            return NodeStatus::FAILURE;
        }       
        return status;
    }

    NodeStatus DurationTrickCmd::onResultReceived(const WrappedResult &result) {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }

