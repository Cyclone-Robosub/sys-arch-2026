#include "server/idle_server.hpp"


IdleActionServer::IdleActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions()) : Node("idle_action_server", options) {
    this->action_server_ = rclcpp_action::create_server<Idle>(
        this, "sleep_service", std::bind(&IdleActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&IdleActionServer::handle_cancel, this, std::placeholders::_1),
        std::bind(&IdleActionServer::handle_accepted, this, std::placeholders::_1));
}

rclcpp_action::GoalResponse IdleActionServer::handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const Idle::Goal> goal) {
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse IdleActionServer::handle_cancel(const std::shared_ptr<GoalHandleIdle> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void) goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
  }

void IdleActionServer::handle_accepted(const std::shared_ptr<GoalHandleIdle> goal_handle) {
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&IdleActionServer::execute, this, std::placeholders::_1), goal_handle}.detach();
}

void IdleActionServer::execute(const std::shared_ptr<GoalHandleIdle> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(5);
    const auto goal = goal_handle->get_goal();
    auto feedback = std::make_shared<Idle::Feedback>();
    auto result = std::make_shared<Idle::Result>();

    if(goal_handle->is_canceling()) {
        result->success = false;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal canceled");
        return;
    }

    RCLCPP_INFO(this->get_logger(), "No feedback to publish");
    loop_rate.sleep();

    // Check if goal is done
    if (rclcpp::ok()) {
      result->success = true;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    }
}
