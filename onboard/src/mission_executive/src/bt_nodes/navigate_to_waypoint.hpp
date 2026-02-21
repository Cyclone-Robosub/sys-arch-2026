#pragma once

#include <behaviortree_cpp/action_node.h>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <nav2_msgs/action/navigate_to_pose.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>

using NavigateToPoseAction = nav2_msgs::action::NavigateToPose;
using GoalHandleNav = rclcpp_action::ClientGoalHandle<NavigateToPoseAction>;

class NavigateToWaypoint : public BT::StatefulActionNode {
public:
    NavigateToWaypoint(const std::string& name, const BT::NodeConfig& config)
        : StatefulActionNode(name, config) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<double>("x", "Goal X position"),
            BT::InputPort<double>("y", "Goal Y position"),
            BT::InputPort<double>("z", 0.0, "Goal Z position"),
            BT::InputPort<std::string>("frame_id", "map", "Reference frame"),
            BT::InputPort<std::string>("action_name", "navigate_to_pose", "Action server name"),
        };
    }

    BT::NodeStatus onStart() override {
        auto x = getInput<double>("x");
        auto y = getInput<double>("y");
        auto z = getInput<double>("z");
        auto frame = getInput<std::string>("frame_id");
        auto action_name = getInput<std::string>("action_name");

        if (!x || !y) {
            throw BT::RuntimeError("NavigateToWaypoint: missing required x or y input");
        }

        // Get ROS node from blackboard
        auto ros_node = config().blackboard->get<rclcpp::Node::SharedPtr>("ros_node");

        if (!action_client_) {
            action_client_ = rclcpp_action::create_client<NavigateToPoseAction>(
                ros_node, action_name.value());
        }

        if (!action_client_->wait_for_action_server(std::chrono::seconds(1))) {
            RCLCPP_WARN(ros_node->get_logger(),
                "NavigateToWaypoint: action server '%s' not available",
                action_name.value().c_str());
            return BT::NodeStatus::FAILURE;
        }

        // Build goal
        auto goal = NavigateToPoseAction::Goal();
        goal.pose.header.frame_id = frame.value();
        goal.pose.header.stamp = ros_node->now();
        goal.pose.pose.position.x = x.value();
        goal.pose.pose.position.y = y.value();
        goal.pose.pose.position.z = z.value();
        goal.pose.pose.orientation.w = 1.0;  // Identity quaternion

        // Send goal
        auto send_goal_options = rclcpp_action::Client<NavigateToPoseAction>::SendGoalOptions();
        auto future = action_client_->async_send_goal(goal, send_goal_options);

        // Wait briefly for goal acceptance
        if (future.wait_for(std::chrono::seconds(2)) != std::future_status::ready) {
            RCLCPP_WARN(ros_node->get_logger(), "NavigateToWaypoint: goal send timed out");
            return BT::NodeStatus::FAILURE;
        }

        goal_handle_ = future.get();
        if (!goal_handle_) {
            RCLCPP_WARN(ros_node->get_logger(), "NavigateToWaypoint: goal rejected");
            return BT::NodeStatus::FAILURE;
        }

        RCLCPP_INFO(ros_node->get_logger(),
            "NavigateToWaypoint: navigating to (%.2f, %.2f, %.2f)",
            x.value(), y.value(), z.value());

        result_ready_ = false;
        result_success_ = false;
        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override {
        if (!goal_handle_) {
            return BT::NodeStatus::FAILURE;
        }

        auto status = goal_handle_->get_status();

        if (status == rclcpp_action::GoalStatus::STATUS_SUCCEEDED) {
            return BT::NodeStatus::SUCCESS;
        } else if (status == rclcpp_action::GoalStatus::STATUS_ABORTED ||
                   status == rclcpp_action::GoalStatus::STATUS_CANCELED) {
            return BT::NodeStatus::FAILURE;
        }

        return BT::NodeStatus::RUNNING;
    }

    void onHalted() override {
        if (goal_handle_) {
            action_client_->async_cancel_goal(goal_handle_);
            goal_handle_.reset();
        }
    }

private:
    rclcpp_action::Client<NavigateToPoseAction>::SharedPtr action_client_;
    GoalHandleNav::SharedPtr goal_handle_;
    bool result_ready_ = false;
    bool result_success_ = false;
};
