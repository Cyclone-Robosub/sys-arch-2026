#include "commands/idle.hpp"

using idle = custom_interfaces::action::idle; // idk what this does but this was here before

namespace CycloneCommands {
    Idle::Idle(const std::string& name, const NodeConfig& conf, const RosNodeParams& params) {

    }
    
    static BT::PortsList providedPorts() {
        return providedBasicPorts({});
    }

    bool Idle::setGoal(Goal& goal) {
        return true;
    }

    NodeStatus Idle::onFailure(ActionNodeErrorCode error) {
        RCLCPP_ERROR(logger(), "Error: %d", error);
        return NodeStatus::FAILURE;
    }

    NodeStatus Idle::onFeedback(const std::shared_ptr<const Feedback> feedback) {
        // return NodeStatus::RUNNING;
        return NodeStatus::RUNNING; 

    }

    NodeStatus Idle::tick() {
        NodeStatus status = RosActionNode<cyclone_msgs::action::Idle>::tick();

        return status;

    }

    NodeStatus onResultReceived(const WrappedResult& wr) {
        return NodeStatus::FAILURE;
    }

}