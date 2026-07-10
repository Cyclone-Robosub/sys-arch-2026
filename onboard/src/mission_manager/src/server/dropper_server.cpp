#include "server/dropper_server.hpp"


DropperActionServer::DropperActionServer(const rclcpp::NodeOptions& options) : Node("dropper_action_server", options) {
    process_done = false;
    goal_publisher = this->create_publisher<std_msgs::msg::UInt8>("manipulator_cmd", 10);
    result_subscriber = this->create_subscription<custom_interfaces::msg::Result>("command_result", 10, std::bind(&DropperActionServer::result_callback, this, std::placeholders::_1));
    this->action_server_ = rclcpp_action::create_server<Dropper>(
        this, "dropper_service", std::bind(&DropperActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
        std::bind(&DropperActionServer::handle_cancel, this, std::placeholders::_1),
        std::bind(&DropperActionServer::handle_accepted, this, std::placeholders::_1));
}

rclcpp_action::GoalResponse DropperActionServer::handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const Dropper::Goal> goal) {
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
}

rclcpp_action::CancelResponse DropperActionServer::handle_cancel(const std::shared_ptr<GoalHandleDropper> goal_handle) {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void) goal_handle;
    return rclcpp_action::CancelResponse::ACCEPT;
  }

void DropperActionServer::handle_accepted(const std::shared_ptr<GoalHandleDropper> goal_handle) {
    // this needs to return quickly to avoid blocking the executor, so spin up a new thread
    std::thread{std::bind(&DropperActionServer::execute, this, std::placeholders::_1), goal_handle}.detach();
}

void DropperActionServer::execute(const std::shared_ptr<GoalHandleDropper> goal_handle) {
    process_done = false;
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(5);
    const auto goal = goal_handle->get_goal();

    auto goal_cmd = std_msgs::msg::UInt8();
    goal_cmd.data = goal->dropper_id;
    goal_publisher->publish(goal_cmd);
    
    auto feedback = std::make_shared<Dropper::Feedback>();
    auto result = std::make_shared<Dropper::Result>(); 

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
void DropperActionServer::result_callback(custom_interfaces::msg::Result::SharedPtr msg) {
    cur_result = msg->success;
    process_done = true;
}
