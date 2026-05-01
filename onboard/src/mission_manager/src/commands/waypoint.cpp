#include "commands/waypoint.hpp"

using namespace BT;
using Pose6D = custom_interfaces::msg::Pose6D;
using WaypointMask = custom_interfaces::msg::WaypointMask;

namespace CycloneCommands
{
    Waypoint::Waypoint(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
    : RosActionNode<custom_interfaces::action::Waypoint>(name, conf, params) {}

    PortsList Waypoint::providedPorts()
    {
    return providedBasicPorts({ InputPort<Pose6D>("waypoint"), InputPort<WaypointMask>("waypoint_mask"),
                                InputPort<Pose6D>("tolerance"), InputPort<double>("hold_time") });
    }

    bool Waypoint::setGoal(RosActionNode::Goal& goal)
    {
    // get parameters from the Input port
    getInput("waypoint", goal.waypoint);
    getInput("waypoint_mask", goal.waypoint_mask);
    getInput("tolerance", goal.tolerance);
    getInput("hold_time", goal.hold_time);
    return true;
    }

    BT::NodeStatus Waypoint::onResultReceived(const WrappedResult& result)
    {
    return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }
}  // namespace CycloneCommands
