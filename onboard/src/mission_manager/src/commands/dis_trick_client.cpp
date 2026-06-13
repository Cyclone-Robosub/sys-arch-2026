#include "commands/dis_trick_client.hpp"

using namespace CycloneCommands;

DistanceTrickCmd::DistanceTrickCmd (const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
 : RosActionNode (name, conf, params) {
}

PortsList DistanceTrickCmd::providedPorts() {
    return providedBasicPorts({
        InputPort<std::string>("trick"),
        InputPort<Pose6D>("end_waypoint_body"),
        InputPort<WaypointMask>("waypoint_mask"),
        InputPort<Pose6D>("tolerence"),
        InputPort<uint64_t>("hold_time"),
        InputPort<double>("timeout")
    });
}

bool DistanceTrickCmd::setGoal(Goal& goal) {
    getInput("trick", goal.trick);
    getInput("end_waypoint_body", goal.end_waypoint_body);
    getInput("waypoint_mask", goal.waypoint_mask);
    getInput("tolerance", goal.tolerance);
    getInput("hold_time", goal.hold_time);
    getInput("timeout", goal.timeout);
    start_time = std::chrono::steady_clock::now();
    timeout_sec = goal.timeout;
    return true;
}

NodeStatus DistanceTrickCmd::tick() {
    NodeStatus status = RosActionNode::tick();

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double>(now - start_time).count();
    if (timeout_sec > 0 && elapsed > timeout_sec) {
        RCLCPP_ERROR(logger(), "Error: timeout");
        return NodeStatus::FAILURE;
    }
    
    return status;
}

NodeStatus DistanceTrickCmd::onResultReceived (const WrappedResult& result) {
    return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
}
