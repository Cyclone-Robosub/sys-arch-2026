#include "server/waypoint_server.hpp"


WaypointActionServer::WaypointActionServer(const rclcpp::NodeOptions& options) : Node("waypoint_action_server", options) {
    process_done = false;
    goal_publisher = this->create_publisher<custom_interfaces::msg::Goal>("command_msg", 10);
    result_subscriber = this->create_subscription<custom_interfaces::msg::Result>("command_result", 10, std::bind(&WaypointActionServer::result_callback, this, std::placeholders::_1));
    this->action_server_ = rclcpp_action::create_server<Waypoint>(
        this, "waypoint_service", std::bind(&WaypointActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&WaypointActionServer::handle_cancel, this, std::placeholders::_1),
        std::bind(&WaypointActionServer::handle_accepted, this, std::placeholders::_1));
}

rclcpp_action::GoalResponse WaypointActionServer::handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const Waypoint::Goal> goal) {
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse WaypointActionServer::handle_cancel(const std::shared_ptr<GoalHandleWaypoint> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void) goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
  }

void WaypointActionServer::handle_accepted(const std::shared_ptr<GoalHandleWaypoint> goal_handle) {
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&WaypointActionServer::execute, this, std::placeholders::_1), goal_handle}.detach();
}

void WaypointActionServer::execute(const std::shared_ptr<GoalHandleWaypoint> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(5);
    const auto goal = goal_handle->get_goal();

    std::string command = "drv_to_world_wp_";
    auto goal_cmd = custom_interfaces::msg::Goal();
    goal_cmd.command_id = command;
    goal_cmd.waypoint = goal->waypoint;
    goal_cmd.waypoint_mask = goal->waypoint_mask;
    goal_cmd.tolerance = goal->tolerance;
    goal_cmd.hold_time = goal->hold_time;
    goal_publisher->publish(goal_cmd);
    
    auto feedback = std::make_shared<Waypoint::Feedback>();
    auto result = std::make_shared<Waypoint::Result>(); 
    
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
void WaypointActionServer::result_callback(custom_interfaces::msg::Result::SharedPtr msg) {
    cur_result = msg->success;
    process_done = true;
}
