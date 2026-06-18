#include "server/seek_object_server.hpp"


SeekObjectActionServer::SeekObjectActionServer(const rclcpp::NodeOptions& options) : Node("seek_object_action_server", options) {
    goal_publisher = this->create_publisher<custom_interfaces::msg::Goal>("command_msg", 10);
    result_subscriber = this->create_subscription<custom_interfaces::msg::Result>("command_result", 10, std::bind(&SeekObjectActionServer::result_callback, this, std::placeholders::_1));
    this->action_server_ = rclcpp_action::create_server<SeekObject>(
        this, "seek_object_service", std::bind(&SeekObjectActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&SeekObjectActionServer::handle_cancel, this, std::placeholders::_1),
        std::bind(&SeekObjectActionServer::handle_accepted, this, std::placeholders::_1));
}

rclcpp_action::GoalResponse SeekObjectActionServer::handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const SeekObject::Goal>) {
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse SeekObjectActionServer::handle_cancel(const std::shared_ptr<GoalHandleSeekObject> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void) goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
  }

void SeekObjectActionServer::handle_accepted(const std::shared_ptr<GoalHandleSeekObject> goal_handle) {
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&SeekObjectActionServer::execute, this, std::placeholders::_1), goal_handle}.detach();
}

void SeekObjectActionServer::execute(const std::shared_ptr<GoalHandleSeekObject> goal_handle) {
    process_done = false;
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(5);
    const auto goal = goal_handle->get_goal();

    std::string command = "drv_to_wp_seek__";
    auto goal_cmd = custom_interfaces::msg::Goal();
    //goal_cmd.command_id = command;
    std::copy(command.begin(), command.end(), goal_cmd.command_id.begin());

    goal_cmd.waypoint = goal->waypoint;
    goal_cmd.waypoint_mask = goal->waypoint_mask;
    std::string object_fixed = "";
    auto object_og = goal->object;
    object_fixed = object_og;
    while (object_fixed.size() < 16) {
        object_fixed += "_";
    }
    //goal_cmd.object = object_fixed;
    std::copy(object_fixed.begin(), object_fixed.end(), goal_cmd.object.begin());

    goal_cmd.confidence = goal->confidence;
    goal_publisher->publish(goal_cmd);
    
    auto feedback = std::make_shared<SeekObject::Feedback>();
    auto result = std::make_shared<SeekObject::Result>(); 

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
      result->found_object = found_object;
      result->reached_waypoint_without_detection = reached_waypoint_without_detection;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal completed");
    }
}
void SeekObjectActionServer::result_callback(custom_interfaces::msg::Result::SharedPtr msg) {
    cur_result = msg->success;
    found_object.assign(msg->found_object.begin(), msg->found_object.end());
    reached_waypoint_without_detection = msg->reached_waypoint_without_detection;
    process_done = true;
}
