#include "include/commands/track_object_waypt_client.hpp"

using namespace BT;

namespace CycloneCommands {
    ObjectWaypt::ObjectWaypt( const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<ObjectWaypt>(name, conf, params) {
        // startTime = std::chrono::steady_clock::now();        
    }

    static BT::PortsList providedPorts() {
        return providedBasicPorts({InputPort<double[]>("tracking_position"), 
        InputPort<bool[]>("waypoint_mask"), InputPort<std::string>("object"), InputPort<double>("timeout_sec") });
    }

    bool ObjectWaypt::setGoal(RosActionNode::Goal& goal) {
        getInput("trackingPos", goal.tracking_position); 
        getInput("waypointMask", goal.waypoint_mask);
        getInput("object", goal.object);
        // getInput("timeout_sec", goal.timeout_sec);

        start_time = std::chrono::steady_clock::now();        
        getInput("timeout_sec", timeout_sec);
        return true;
    }

    // Based on the reply you may decide to return SUCCESS or FAILURE.
    NodeStatus ObjectWaypt::onResultReceived(const WrappedResult& wr) {
        if (wr.result == "SUCCESS") { 
            return NodeStatus::SUCCESS;
        }
        // } else if (wr.result == "RUNNING") {
        //     return NodeStatus::RUNNING
        // }
        return NodeStatus::FAILURE;
    }

    NodeStatus ObjectWaypt::onFailure(ActionNodeErrorCode error) {
        RCLCPP_ERROR(logger(), "Error: %d", error);
        return NodeStatus::FAILURE;
    }

    NodeStatus ObjectWaypt::onFeedback(const std::shared_ptr<const Feedback> feedback) {
        // implement time out function?
        // double timeout_sec;
        // getInput("timeout_sec", timeout_sec);
        // if (startTime - std::chrono::steady_clock::now() > timeout_sec) {
        //     return NodeStatus::FAILURE;
        // }
        return NodeStatus::RUNNING;


    }

    NodeStatus ObjectWaypt::tick() {
        NodeStatus status = RosActionNode<cyclone_msgs::action::TrackObjectWaypt>::tick();

        if (status == NodeStatus::RUNNING) {
            std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
            double elapsed = std::chrono::duration<double>(now - start_time).count();
            if (elapsed > timeout_sec) {
                RCLCPP_ERROR(logger(), "Error: %d", error);
                return NodeStatus::FAILURE;
            }
        }

        return status;

    }


}