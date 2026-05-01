#include "commands/command_alias.hpp"
#include "commands/object_rel_waypoint.hpp"

namespace CycloneCommands {
    ObjRelWaypointCmd::ObjRelWaypointCmd( const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<ObjectRelWaypoint>(name, conf, params) {
    }

    PortsList ObjRelWaypointCmd::providedPorts() {
        return providedBasicPorts({
            InputPort<Pose6D>("tracking_position"),
            InputPort<WaypointMask>("waypoint_mask"),
            InputPort<std::string>("object"),
            InputPort<Pose6D>("tolerance"),
            InputPort<uint64_t>("hold_time")
        });
    }

    bool ObjRelWaypointCmd::setGoal(Goal& goal) {
        getInput("tracking_position", goal.tracking_position);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("object", goal.object);
        getInput("tolerance", goal.tolerance);
        getInput("hold_time", goal.hold_time);
        return true;
    }

    NodeStatus ObjRelWaypointCmd::onResultReceived (const WrappedResult& result) {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }

}