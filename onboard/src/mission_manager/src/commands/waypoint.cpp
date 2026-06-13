#include "commands/command_alias.hpp"
#include "commands/waypoint.hpp"

using namespace CycloneCommands;

    WaypointCmd::WaypointCmd(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
    : RosActionNode(name, conf, params) {}

    PortsList WaypointCmd::providedPorts()
    {
        return providedBasicPorts({
            InputPort<Vector3>("world_waypoint_pos"),
            InputPort<Vector3>("world_waypoint_orient"),
            InputPort<Vector3>("waypoint_mask_pos"),
            InputPort<Vector3>("waypoint_mask_orient"),
            InputPort<Vector3>("tolerance_pos"),
            InputPort<Vector3>("tolerance_orient"),
            InputPort<double>("hold_time")
        });
    }

    bool WaypointCmd::setGoal(Goal& goal) {
        // get parameters from the Input port
        getInput("world_waypoint_pos", goal.waypoint_position);
        getInput("world_waypoint_orient", goal.waypoint_orientation);
        getInput("waypoint_mask_pos", goal.waypoint_mask_position);
        getInput("waypoint_mask_orient", goal.waypoint_mask_orientation);
        getInput("tolerance_pos", goal.tolerance_position);
        getInput("tolerance_orient", goal.tolerance_orientation);
        getInput("hold_time", goal.hold_time);

        start_time = std::chrono::steady_clock::now();
        timeout_sec = goal.hold_time + std::chrono::milliseconds(10).count(); 
        return true;
    }

    NodeStatus WaypointCmd::tick() {
        NodeStatus status = RosActionNode::tick();

        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(now - start_time).count();
        if (elapsed > timeout_sec) {
            RCLCPP_ERROR(logger(), "Error: timeout");
            return NodeStatus::FAILURE;
        }       
        return status;
    }

    NodeStatus WaypointCmd::onResultReceived(const WrappedResult& result) {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }
 // namespace CycloneCommands
