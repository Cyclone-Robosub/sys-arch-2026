#include "server/distance_trick_server.hpp"


DistanceTrickActionServer::DistanceTrickActionServer(const rclcpp::NodeOptions& options) : Node("distance_trick_action_server", options) {
    process_done = false;
    goal_publisher = this->create_publisher<custom_interfaces::msg::Goal>("command_msg", 10);
    result_subscriber = this->create_subscription<custom_interfaces::msg::Result>("command_result", 10, std::bind(&DistanceTrickActionServer::result_callback, this, std::placeholders::_1));
    this->action_server_ = rclcpp_action::create_server<DistanceTrick>(
        this, "distance_trick_service", std::bind(&DistanceTrickActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&DistanceTrickActionServer::handle_cancel, this, std::placeholders::_1),
        std::bind(&DistanceTrickActionServer::handle_accepted, this, std::placeholders::_1));
}

rclcpp_action::GoalResponse DistanceTrickActionServer::handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const DistanceTrick::Goal> goal [[maybe_unused]]) {
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse DistanceTrickActionServer::handle_cancel(const std::shared_ptr<GoalHandleDistanceTrick> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void) goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
  }

void DistanceTrickActionServer::handle_accepted(const std::shared_ptr<GoalHandleDistanceTrick> goal_handle) {
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&DistanceTrickActionServer::execute, this, std::placeholders::_1), goal_handle}.detach();
}

void DistanceTrickActionServer::execute(const std::shared_ptr<GoalHandleDistanceTrick> goal_handle) {
    process_done = false;
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(5);
    const auto goal = goal_handle->get_goal();

    std::string command = "distance_trick__";
    auto goal_cmd = custom_interfaces::msg::Goal();
    //goal_cmd.command_id = command;
    std::copy(command.begin(), command.end(), goal_cmd.command_id.begin());
 
    auto trick_og = goal->trick;
    std::string trick_fixed = "";
    if (trick_og == "drive_to_body_relative_waypoint") {
        trick_fixed = "drv_to_body_wp__";
    } else {
        trick_fixed = trick_og;
    }
    while (trick_fixed.size() < 16) {
        trick_fixed += "_";
    }

    //goal_cmd.trick = trick_fixed;
    std::copy(trick_fixed.begin(), trick_fixed.end(), goal_cmd.trick.begin());
    goal_cmd.waypoint = goal->end_waypoint_body;
    goal_cmd.waypoint_mask = goal->waypoint_mask;
   
    goal_cmd.tolerance = goal->tolerance;
    goal_cmd.hold_time = goal->hold_time;
    goal_publisher->publish(goal_cmd);
    
    auto feedback = std::make_shared<DistanceTrick::Feedback>();
    auto result = std::make_shared<DistanceTrick::Result>(); 

    while (!process_done) {
        if (goal_handle->is_canceling()) {
            result->success = false;
            goal_handle->canceled(result);
            RCLCPP_INFO(this->get_logger(), "Goal canceled");
            return;
        }
        //RCLCPP_INFO(this->get_logger(), "No feedback to publish");
        loop_rate.sleep();
    }
    
    if (rclcpp::ok()) {
      result->success = cur_result;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal completed");
    }
}
void DistanceTrickActionServer::result_callback(custom_interfaces::msg::Result::SharedPtr msg) {
    cur_result = msg->success;
    process_done = true;
}
