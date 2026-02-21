#pragma once

// TODO: Once ManipulateObject.action is defined in crs_ros2_interfaces,
// change this to extend RosActionNode<ManipulateObject> like NavigateToWaypoint.
//
// For now, this is a sync action that publishes Int64 to the
// manipulationCommand topic (matching the original WaypointExecutive behavior)
// to allow testing before the action interface is ready.

#include <behaviortree_cpp/action_node.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/int64.hpp>
#include <mission_executive/types.hpp>

using namespace mission_executive;

class SendManipulatorCommand : public BT::SyncActionNode {
public:
    SendManipulatorCommand(const std::string& name, const BT::NodeConfig& config)
        : SyncActionNode(name, config) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<ManipulatorCommand>("command", "Manipulator command to send"),
        };
    }

    BT::NodeStatus tick() override {
        auto cmd = getInput<ManipulatorCommand>("command");
        if (!cmd) {
            throw BT::RuntimeError("SendManipulatorCommand: missing required 'command' input");
        }

        // Get ROS node from blackboard to create publisher
        auto ros_node = config().blackboard->get<rclcpp::Node::SharedPtr>("ros_node");
        if (!manip_pub_) {
            manip_pub_ = ros_node->create_publisher<std_msgs::msg::Int64>(
                "manipulationCommand", 10);
        }

        auto msg = std_msgs::msg::Int64();
        msg.data = static_cast<int64_t>(cmd.value());
        manip_pub_->publish(msg);

        RCLCPP_INFO(ros_node->get_logger(),
            "SendManipulatorCommand: sent command %s (%ld)",
            toString(cmd.value()).c_str(), msg.data);

        return BT::NodeStatus::SUCCESS;
    }

private:
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr manip_pub_;
};
