#include <functional>
#include <memory>
#include <thread>

#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "custom_interfaces/action/dropper.hpp"
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/msg/result.hpp"

class DropperActionServer : public rclcpp::Node {
public:
  using Dropper = custom_interfaces::action::Dropper;
  using GoalHandleDropper = rclcpp_action::ServerGoalHandle<Dropper>;
  explicit DropperActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
private:
  rclcpp_action::Server<Dropper>::SharedPtr action_server_;
  
  rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr goal_publisher;
  rclcpp::Subscription<custom_interfaces::msg::Result>::SharedPtr result_subscriber;
  bool process_done;
  void result_callback(custom_interfaces::msg::Result::SharedPtr msg);
  bool cur_result;

  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const Dropper::Goal> goal);
  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleDropper> goal_handle);
  void handle_accepted(const std::shared_ptr<GoalHandleDropper> goal_handle);
  void execute(const std::shared_ptr<GoalHandleDropper> goal_handle);
};  