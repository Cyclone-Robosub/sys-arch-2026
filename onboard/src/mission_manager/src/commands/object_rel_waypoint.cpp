#include "commands/command_alias.hpp"
#include "commands/object_rel_waypoint.hpp"

using namespace CycloneCommands;
    ObjRelWaypointCmd::ObjRelWaypointCmd( const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
     : RosActionNode (name, conf, params) {}

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

        start_time = std::chrono::steady_clock::now();
        timeout_sec = goal.hold_time + std::chrono::milliseconds(10).count(); 
        return true;
    }

    NodeStatus ObjRelWaypointCmd::tick() {
        NodeStatus status = RosActionNode::tick();

        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        double elapsed = std::chrono::duration<double>(now - start_time).count();
        if (elapsed > timeout_sec) {
            RCLCPP_ERROR(logger(), "Error: timeout");
            return NodeStatus::FAILURE;
        }       
        return status;
    }

    NodeStatus ObjRelWaypointCmd::onResultReceived (const WrappedResult& result) {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }

