#include "include/commands/object_rel_waypoint.hpp"

using namespace BT;

namespace CycloneCommands {
    ObjectWaypt::ObjectWaypt( const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<ObjectWaypt>(name, conf, params) {    
    }

    static BT::PortsList providedPorts() {
        return providedBasicPorts({
            InputPort<Pose6D>("tracking_position"),
            InputPort<WaypointMask>("waypoint_mask"),
            InputPort<std::string>("object"),
            InputPort<Pose6D>("tolerence"),
            InputPort<uint64_t>("hold_time")
        });
    }

    bool ObjectWaypt::setGoal(RosActionNode::Goal& goal) {
        getInput("tracking_position", goal.tracking_position);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("object", goal.object);
        getInput("tolerence", goal.tolerence);
        getInput("hold_time", goal.hold_time);
        return true;
    }

    NodeStatus DisTrick::onResultReceived (const WrappedResult& result) override {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }

}