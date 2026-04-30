#include "include/commands/duration_trick_client.hpp"

using namespace BT;

namespace CycloneCommands {
    DurationTrick::DurationTrick(const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<WayptAbs>(name, conf, params) {
    }

    static PortsList providedPorts() {
        return providedBasicPorts({
            InputPort<std::string>("trick"),
            InputPort<uint64_t>("duration")
            InputPort<WaypointMask>("waypoint_mask"),
            InputPort<Pose6D>("tolerence"),
            InputPort<uint64_t>("hold_time")
        });
    }

    bool DurationTrick::setGoal(RosActionNode::Goal& goal) override {
        getInput("trick", goal.trick);
        getInput("duration", goal.duration);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("hold_time", goal.hold_time);
        // return true, if we were able to set the goal correctly.
        return true;
    }
    
    NodeStatus DurationTrick::onFeedback(const std::shared_ptr<const Feedback> feedback) override {
        std::cout << feedback->remaining_duration << "\n";
        std::cout << feedback->time_in_tolerance << "\n";
        return NodeStatus::RUNNING;
    }

    NodeStatus DisTrick::onResultReceived (const WrappedResult& result) override {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }

}
