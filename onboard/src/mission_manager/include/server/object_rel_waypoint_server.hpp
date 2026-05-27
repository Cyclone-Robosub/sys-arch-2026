#include <functional>
#include <memory>
#include <thread>

#include "std_msgs/msg/bool.hpp"
#include "custom_interfaces/msg/goal.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "custom_interfaces/action/object_relative_waypoint.hpp"
#include "behaviortree_ros2/bt_action_node.hpp"

class ObjRelWaypointActionServer : public rclcpp::Node {
public:
  using ObjRelWaypoint = custom_interfaces::action::ObjectRelativeWaypoint;
  using GoalHandleObjRelWaypoint = rclcpp_action::ServerGoalHandle<ObjRelWaypoint>;
  explicit ObjRelWaypointActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
private:
  rclcpp_action::Server<ObjRelWaypoint>::SharedPtr action_server_;
  
  rclcpp::Publisher<custom_interfaces::msg::Goal>::SharedPtr goal_publisher;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr result_subscriber;
  void result_callback(std_msgs::msg::Bool::SharedPtr msg);
  bool cur_result;

  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const ObjRelWaypoint::Goal> goal);
  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleObjRelWaypoint> goal_handle);
  void handle_accepted(const std::shared_ptr<GoalHandleObjRelWaypoint> goal_handle);
  void execute(const std::shared_ptr<GoalHandleObjRelWaypoint> goal_handle);
};  