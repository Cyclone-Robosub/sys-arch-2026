#include "server/duration_trick_server.hpp"


DurationTrickActionServer::DurationTrickActionServer(const rclcpp::NodeOptions& options) : Node("duration_trick_action_server", options) {
    process_done = false;
    goal_publisher = this->create_publisher<custom_interfaces::msg::Goal>("command_msg", 10);
    result_subscriber = this->create_subscription<custom_interfaces::msg::Result>("command_result", 10, std::bind(&DurationTrickActionServer::result_callback, this, std::placeholders::_1));
    this->action_server_ = rclcpp_action::create_server<DurationTrick>(
        this, "duration_trick_service", std::bind(&DurationTrickActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&DurationTrickActionServer::handle_cancel, this, std::placeholders::_1),
        std::bind(&DurationTrickActionServer::handle_accepted, this, std::placeholders::_1));
}

rclcpp_action::GoalResponse DurationTrickActionServer::handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const DurationTrick::Goal> goal) {
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse DurationTrickActionServer::handle_cancel(const std::shared_ptr<GoalHandleDurationTrick> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void) goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
  }

void DurationTrickActionServer::handle_accepted(const std::shared_ptr<GoalHandleDurationTrick> goal_handle) {
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&DurationTrickActionServer::execute, this, std::placeholders::_1), goal_handle}.detach();
}

void DurationTrickActionServer::execute(const std::shared_ptr<GoalHandleDurationTrick> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(5);
    const auto goal = goal_handle->get_goal();

    std::string command = "duration_trick__";
    auto goal_cmd = custom_interfaces::msg::Goal();
    goal_cmd.command_id = command;

    std::string trick_fixed = "";
    auto trick_og = goal->trick;

    trick_fixed = trick_og;
    while (trick_fixed.size() < 16) {
        trick_fixed += "_";
    }
    goal_cmd.trick = trick_fixed;
    goal_cmd.duration = goal->duration;
   
    //goal_cmd.waypoint_mask = goal->waypoint_mask;
   
    //goal_cmd.tolerance = goal->tolerance;
    goal_cmd.hold_time = goal->hold_time;
    goal_publisher->publish(goal_cmd);
    
    auto feedback = std::make_shared<DurationTrick::Feedback>();
    auto result = std::make_shared<DurationTrick::Result>(); 

    while (!process_done) {
        if (goal_handle->is_canceling()) {
            result->success = false;
            goal_handle->canceled(result);
            RCLCPP_INFO(this->get_logger(), "Goal canceled");
            return;
        }   
        RCLCPP_INFO(this->get_logger(), "No feedback to publish");
        loop_rate.sleep();
    }
    // Check if goal is done
    if (rclcpp::ok()) {
      result->success = cur_result;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    }
}
void DurationTrickActionServer::result_callback(custom_interfaces::msg::Result::SharedPtr msg) {
    cur_result = msg->success;
    process_done = true;
}
