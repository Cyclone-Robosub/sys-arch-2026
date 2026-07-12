#include "commands/command_alias.hpp"
#include "commands/waypoint.hpp"

using namespace CycloneCommands;

WaypointCmd::WaypointCmd(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
    : RosActionNode(name, conf, params) {}

PortsList WaypointCmd::providedPorts() {
    return providedBasicPorts({
        InputPort<Pose6D>("world_waypoint"),
        InputPort<WaypointMask>("waypoint_mask"),
        InputPort<Pose6D>("tolerance"),
        InputPort<double>("hold_time"),
        InputPort<double>("timeout")
    });
}

bool WaypointCmd::setGoal(Goal& goal) {
    // get parameters from the Input port
    getInput("world_waypoint", goal.waypoint);
    getInput("waypoint_mask", goal.waypoint_mask);
    getInput("tolerance", goal.tolerance);
    getInput("hold_time", goal.hold_time);
    getInput("timeout", goal.timeout);
    RCLCPP_INFO(logger(), "%f", goal.timeout);
    

    start_time = std::chrono::steady_clock::now();
    timeout_sec = goal.timeout;
    return true;
}

NodeStatus WaypointCmd::tick() {
    NodeStatus status = RosActionNode::tick();

    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    double elapsed = std::chrono::duration<double>(now - start_time).count();
    if ((timeout_sec > 0) && (elapsed > timeout_sec)) {
        RCLCPP_ERROR(logger(), "Drive to World Waypoint - Error: timeout");
        halt();
        return NodeStatus::FAILURE;
    } else if (timeout_sec <= 0) {
        RCLCPP_ERROR(logger(), "Drive to World Waypoint - Invalid timeout");
        halt();
        return NodeStatus::FAILURE;
    }
    return status;
}

NodeStatus WaypointCmd::onResultReceived(const WrappedResult& result) {
    return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
}
 // namespace CycloneCommands
