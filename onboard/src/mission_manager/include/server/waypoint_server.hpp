#include <functional>
#include <memory>
#include <thread>

#include "std_msgs/msg/bool.hpp"
#include "custom_interfaces/msg/result.hpp"
#include "custom_interfaces/msg/goal.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "custom_interfaces/action/waypoint.hpp"
#include "behaviortree_ros2/bt_action_node.hpp"

class WaypointActionServer : public rclcpp::Node {
public:
  using Waypoint = custom_interfaces::action::Waypoint;
  using GoalHandleWaypoint = rclcpp_action::ServerGoalHandle<Waypoint>;
  explicit WaypointActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
private:
  rclcpp_action::Server<Waypoint>::SharedPtr action_server_;
  rclcpp::Publisher<custom_interfaces::msg::Goal>::SharedPtr goal_publisher;
  rclcpp::Subscription<custom_interfaces::msg::Result>::SharedPtr result_subscriber;
  bool process_done;
  void result_callback(custom_interfaces::msg::Result::SharedPtr msg);
  bool cur_result;

  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const Waypoint::Goal> goal);
  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleWaypoint> goal_handle);
  void handle_accepted(const std::shared_ptr<GoalHandleWaypoint> goal_handle);
  void execute(const std::shared_ptr<GoalHandleWaypoint> goal_handle);
};  