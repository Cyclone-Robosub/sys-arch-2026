#include "include/commands/track_object_waypt_client.hpp"

using namespace BT;

namespace CycloneCommand {
    ObjectWaypt::ObjectWaypt( const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<ObjectWaypt>(name, conf, params) {
        startTime = std::chrono::steady_clock::now();        
    }

    static BT::PortsList providedPorts() {
        return providedBasicPorts{InputPort<float64[]>("trackingPos"), 
        InputPort<bool[]>("waypointMask"), InputPort<std::string>("object") };
    }

    bool ObjectWaypt::setGoal(RosActionNode::Goal& goal) {
        getInput("trackingPos", goal.tracking_position); 
        getInput("waypointMask", goal.waypoint_mask);
        getInput("object", goal.object);

        return true;
    }

    // Based on the reply you may decide to return SUCCESS or FAILURE.
    NodeStatus onResultReceived(const WrappedResult& wr) override {
        if (wr.result ->  ) { 
            return NodeStatus::SUCCESS;
        } else if () {
         
        }   return//  NodeStatus::RUNNING;
        }
        return NodeStatus::FAILURE;
//     }

    NodeStatus ObjectWaypt::onFai// lure(ActionNodeErrorCode error) {
        RCLCPP_ERROR(logger(), "Error: %d", error);
        return NodeStatus::FAILURE;
    }

    NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback) {
        return NodeStatus::RUNNING;
    }


}