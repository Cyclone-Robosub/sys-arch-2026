#include "commands/command_alias.hpp"
#include "commands/seek_object.hpp"
#include "rclcpp/logging.hpp"

namespace CycloneCommands {
    SeekObjCmd::SeekObjCmd(const std::string& name, const NodeConfig& conf, const RosNodeParams& params)
     : RosActionNode(name, conf, params) {}

    PortsList SeekObjCmd::providedPorts(){
        return providedBasicPorts({
            InputPort<Pose6D>("waypoint"),
            InputPort<WaypointMask>("waypoint_mask"),
            InputPort<std::string>("object"),
            InputPort<Pose6D>("tolerance"),
            InputPort<double>("confidence"),
            InputPort<uint64_t>("hold_time"),
            OutputPort<std::string>("found_object"),
            OutputPort<bool>("reached_waypoint_without_detection")
        });
    }

    bool SeekObjCmd::setGoal(Goal& goal) {
        // get parameters from the Input port
        getInput("waypoint", goal.waypoint);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("object", goal.object);
        getInput("tolerance", goal.tolerance);
        getInput("confidence", goal.confidence);
        getInput("hold_time", goal.hold_time);
        // return true, if we were able to set the goal correctly.
        return true;
    }

    NodeStatus SeekObjCmd::onResultReceived(const WrappedResult& result) {
        if(result.result->success) {
            setOutput("found_object", result.result->found_object);
            return NodeStatus::SUCCESS;
        }
        if(result.result->reached_waypoint_without_detection) {
            RCLCPP_WARN(logger(), "Reached seek waypoint but did not find object: %s",
                        goal_object_id_.c_str());
        }
        return NodeStatus::FAILURE;
    }
}