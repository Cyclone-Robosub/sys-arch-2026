#include "commands/dis_trick_client.hpp"

namespace CycloneCommands {
    DistanceTrickCmd::DistanceTrickCmd (const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
     : RosActionNode<DistanceTrick> (name, conf, params) {}

    PortsList DistanceTrickCmd::providedPorts() {
        return providedBasicPorts({
            InputPort<std::string>("trick"),
            InputPort<Pose6D>("end_waypoint_body"),
            InputPort<WaypointMask>("waypoint_mask"),
            InputPort<Pose6D>("tolerence"),
            InputPort<uint64_t>("hold_time")
        });
    }
    
    bool DistanceTrickCmd::setGoal(Goal& goal) {
        getInput("trick", goal.trick);
        getInput("end_waypoint_body", goal.end_waypoint_body);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("tolerance", goal.tolerance);
        getInput("hold_time", goal.hold_time);
        return true;
    }

    NodeStatus DistanceTrickCmd::onResultReceived (const WrappedResult& result) {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }
};