#include <functional>
#include <memory>
#include <thread>

#include "std_msgs/msg/bool.hpp"
#include "custom_interfaces/msg/goal.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "custom_interfaces/action/distance_trick.hpp"
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/msg/result.hpp"

class DistanceTrickActionServer : public rclcpp::Node {
public:
  using DistanceTrick = custom_interfaces::action::DistanceTrick;
  using GoalHandleDistanceTrick = rclcpp_action::ServerGoalHandle<DistanceTrick>;
  explicit DistanceTrickActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
private:
  rclcpp_action::Server<DistanceTrick>::SharedPtr action_server_;
  
  rclcpp::Publisher<custom_interfaces::msg::Goal>::SharedPtr goal_publisher;
  rclcpp::Subscription<custom_interfaces::msg::Result>::SharedPtr result_subscriber;
  bool process_done;
  void result_callback(custom_interfaces::msg::Result::SharedPtr msg);
  bool cur_result;

  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const DistanceTrick::Goal> goal);
  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleDistanceTrick> goal_handle);
  void handle_accepted(const std::shared_ptr<GoalHandleDistanceTrick> goal_handle);
  void execute(const std::shared_ptr<GoalHandleDistanceTrick> goal_handle);
};  