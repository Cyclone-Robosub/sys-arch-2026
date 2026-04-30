#include "include/commands/waypoint.hpp"

using namespace BT;

namespace CycloneCommands {
    WayptAbs::WayptAbs(const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<WayptAbs>(name, conf, params) {
        // startTime = std::chrono::steady_clock::now();
        // feedback_.delta = {0, 0, 0, 0, 0, 0};
        // feedback_.time_in_tolerance = 0;
    }

    static PortsList providedPorts() {
        return providedBasicPorts({
            InputPort<Pose6D>("waypoint"),
            InputPort<WaypointMask>("waypoint_mask"),
            InputPort<Pose6D>("tolerance"),
            InputPort<Double("hold_time")
        });
    }

    bool WayptAbs::setGoal(RosActionNode::Goal& goal) override {
        // get parameters from the Input port
        getInput("waypoint", goal.waypoint);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("tolerance", goal.tolerance);
        getInput("hold_time", goal.hold_time);
        return true;
    }

    BT::NodeStatus onResultReceived(const WrappedResult& result)
    {
        return result.result->success ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
    }

}
