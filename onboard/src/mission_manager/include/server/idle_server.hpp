#include <functional>
#include <memory>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "custom_interfaces/action/idle.hpp"
#include "behaviortree_ros2/bt_action_node.hpp"

class IdleActionServer : public rclcpp::Node {
public:
  using Idle = custom_interfaces::action::Idle;
  using GoalHandleIdle = rclcpp_action::ServerGoalHandle<Idle>;
  explicit IdleActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());

private:
  
  rclcpp_action::Server<Idle>::SharedPtr action_server_;
  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const Idle::Goal> goal);
  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleIdle> goal_handle);
  void handle_accepted(const std::shared_ptr<GoalHandleIdle> goal_handle);
  void execute(const std::shared_ptr<GoalHandleIdle> goal_handle);
   
};  