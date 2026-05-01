#include "commands/duration_trick_client.hpp"

namespace CycloneCommands {
    DurationTrickCmd::DurationTrickCmd(const std::string &name, const NodeConfig &conf,
                                       const RosNodeParams &params) : RosActionNode(name, conf, params) {}

    PortsList DurationTrickCmd::providedPorts() {
        return providedBasicPorts({
            InputPort<std::string>("trick"),
            InputPort<uint64_t>("duration"),
            InputPort<WaypointMask>("waypoint_mask"),
            InputPort<Pose6D>("tolerance"),
            InputPort<uint64_t>("hold_time")
        });
    }

    bool DurationTrickCmd::setGoal(Goal &goal) {
        getInput("trick", goal.trick);
        getInput("duration", goal.duration);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("hold_time", goal.hold_time);
        // return true, if we were able to set the goal correctly.
        return true;
    }

    NodeStatus DurationTrickCmd::onResultReceived(const WrappedResult &result) {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }
}
