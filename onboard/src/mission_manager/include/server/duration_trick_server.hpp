#include <functional>
#include <memory>
#include <thread>

#include "std_msgs/msg/bool.hpp"
#include "custom_interfaces/msg/goal.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "custom_interfaces/action/duration_trick.hpp"
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/msg/result.hpp"

class DurationTrickActionServer : public rclcpp::Node {
public:
  using DurationTrick = custom_interfaces::action::DurationTrick;
  using GoalHandleDurationTrick = rclcpp_action::ServerGoalHandle<DurationTrick>;
  explicit DurationTrickActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
private:
  rclcpp_action::Server<DurationTrick>::SharedPtr action_server_;
  
  rclcpp::Publisher<custom_interfaces::msg::Goal>::SharedPtr goal_publisher;
  rclcpp::Subscription<std_msgs::msg::Result>::SharedPtr result_subscriber;
  void result_callback(std_msgs::msg::Result::SharedPtr msg);
  bool cur_result;

  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const DurationTrick::Goal> goal);
  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleDurationTrick> goal_handle);
  void handle_accepted(const std::shared_ptr<GoalHandleDurationTrick> goal_handle);
  void execute(const std::shared_ptr<GoalHandleDurationTrick> goal_handle);
};  