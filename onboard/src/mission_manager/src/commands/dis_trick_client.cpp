#include "commands/dis_trick_client.hpp"

using namespace BT;


namespace CycloneCommands {
    DisTrick::DisTrick(const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<WayptAbs>(name, conf, params) 
    {}

    static PortsList providedPorts() {
        return providedBasicPorts({
            InputPort<std::string>("trick"),
            InputPort<Pose6D>("end_waypoint_body")
            InputPort<WaypointMask>("waypoint_mask"),
            InputPort<Pose6D>("tolerence"),
            InputPort<uint64_t>("hold_time")
        });
    }
    
    bool DisTrick::setGoal(RosActionNode::Goal& goal) override {
        getInput("trick", goal.trick);
        getInput("waypoint", goal.waypoint);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("tolerance", goal.tolerance);
        getInput("hold_time", goal.hold_time);
        return true;
    }

    NodeStatus DisTrick::onResultReceived (const WrappedResult& result) override {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }

}