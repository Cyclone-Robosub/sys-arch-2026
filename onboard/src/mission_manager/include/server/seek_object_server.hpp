#include <functional>
#include <memory>
#include <thread>

#include "std_msgs/msg/bool.hpp"
#include "custom_interfaces/msg/goal.hpp"
#include "custom_interfaces/msg/result.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "custom_interfaces/action/seek_object.hpp"
#include "behaviortree_ros2/bt_action_node.hpp"

class SeekObjectActionServer : public rclcpp::Node {
public:
  using SeekObject = custom_interfaces::action::SeekObject;
  using GoalHandleSeekObject = rclcpp_action::ServerGoalHandle<SeekObject>;
  explicit SeekObjectActionServer(const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
private:
  rclcpp_action::Server<SeekObject>::SharedPtr action_server_;
  
  rclcpp::Publisher<custom_interfaces::msg::Goal>::SharedPtr goal_publisher;
  rclcpp::Subscription<custom_interfaces::msg::Result>::SharedPtr result_subscriber;
  bool process_done;
  void result_callback(custom_interfaces::msg::Result::SharedPtr msg);
  bool cur_result;
  std::string found_object;
  bool reached_waypoint_without_detection;
  
  rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const SeekObject::Goal> goal);
  rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleSeekObject> goal_handle);
  void handle_accepted(const std::shared_ptr<GoalHandleSeekObject> goal_handle);
  void execute(const std::shared_ptr<GoalHandleSeekObject> goal_handle);
};  