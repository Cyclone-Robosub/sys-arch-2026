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

    bool WaypointCmd::setGoal(Goal& goal)
    {
    // get parameters from the Input port
    getInput("waypoint", goal.waypoint);
    getInput("waypoint_mask", goal.waypoint_mask);
    getInput("tolerance", goal.tolerance);
    getInput("hold_time", goal.hold_time);
    return true;
    }

    NodeStatus WaypointCmd::onResultReceived(const WrappedResult& result)
    {
    return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }
 // namespace CycloneCommands
