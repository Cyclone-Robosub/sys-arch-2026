#include "commands/command_alias.hpp"
#include "commands/waypoint.hpp"

using namespace CycloneCommands;

    WaypointCmd::WaypointCmd(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
    : RosActionNode(name, conf, params) {}

    PortsList WaypointCmd::providedPorts()
    {
        return providedBasicPorts({
            InputPort<Pose6D>("waypoint"),
            InputPort<WaypointMask>("waypoint_mask"),
            InputPort<Pose6D>("tolerance"),
            InputPort<double>("hold_time")
        });
    }

    bool WaypointCmd::setGoal(Goal& goal) {
        // get parameters from the Input port
        getInput("waypoint", goal.waypoint);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("tolerance", goal.tolerance);
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

    NodeStatus WaypointCmd::onResultReceived(const WrappedResult& result)
    {
    return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }
 // namespace CycloneCommands
