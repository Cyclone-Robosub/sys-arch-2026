#include "server/object_rel_waypoint_server.hpp"


ObjRelWaypointActionServer::ObjRelWaypointActionServer(const rclcpp::NodeOptions& options) : Node("obj_rel_waypoint_action_server", options) {
    process_done = false;
    goal_publisher = this->create_publisher<custom_interfaces::msg::Goal>("command_msg", 10);
    result_subscriber = this->create_subscription<custom_interfaces::msg::Result>("command_result", 10, std::bind(&ObjRelWaypointActionServer::result_callback, this, std::placeholders::_1));
    this->action_server_ = rclcpp_action::create_server<ObjRelWaypoint>(
        this, "obj_rel_waypoint_service", std::bind(&ObjRelWaypointActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&ObjRelWaypointActionServer::handle_cancel, this, std::placeholders::_1),
        std::bind(&ObjRelWaypointActionServer::handle_accepted, this, std::placeholders::_1));
}

rclcpp_action::GoalResponse ObjRelWaypointActionServer::handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const ObjRelWaypoint::Goal> goal) {
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse ObjRelWaypointActionServer::handle_cancel(const std::shared_ptr<GoalHandleObjRelWaypoint> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void) goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
  }

void ObjRelWaypointActionServer::handle_accepted(const std::shared_ptr<GoalHandleObjRelWaypoint> goal_handle) {
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&ObjRelWaypointActionServer::execute, this, std::placeholders::_1), goal_handle}.detach();
}

void ObjRelWaypointActionServer::execute(const std::shared_ptr<GoalHandleObjRelWaypoint> goal_handle) {
    process_done = false;
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(5);
    const auto goal = goal_handle->get_goal();

    std::string command = "track_obj_wp___";
    auto goal_cmd = custom_interfaces::msg::Goal();
    goal_cmd.command_id = command;
    goal_cmd.waypoint = goal->tracking_position;
    goal_cmd.waypoint_mask = goal->waypoint_mask;
    std::string object_fixed = "";
    auto object_og = goal->object;
    object_fixed = object_og;
    while (object_fixed.size() < 16) {
        object_fixed += "_";
    }
    goal_cmd.object = object_fixed;
    goal_cmd.tolerance = goal->tolerance;
    goal_cmd.hold_time = goal->hold_time;
    goal_publisher->publish(goal_cmd);
    
    auto feedback = std::make_shared<ObjRelWaypoint::Feedback>();
    auto result = std::make_shared<ObjRelWaypoint::Result>(); 

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
    
    if (rclcpp::ok()) {
      result->success = cur_result;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal completed");
    }
}
void ObjRelWaypointActionServer::result_callback(custom_interfaces::msg::Result::SharedPtr msg) {
    cur_result = msg->success;
    process_done = true;
}
