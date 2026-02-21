#pragma once

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/float32_multi_array.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <behaviortree_cpp/bt_factory.h>
#include <behaviortree_cpp/loggers/groot2_publisher.h>

#include <string>
#include <vector>
#include <mutex>

namespace mission_executive {

class MissionExecutorNode : public rclcpp::Node {
public:
    MissionExecutorNode();

    void initialize();

private:
    void registerBTNodes();
    void loadTreeFromParam();
    void seedBlackboardFromParams();
    void setupSubscriptions();
    void tickTree();

    // ROS subscriptions
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr detections_sub_;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr soc_sub_;
    rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr position_sub_;

    // Timer for tree ticking
    rclcpp::TimerBase::SharedPtr tick_timer_;

    // BT components
    BT::BehaviorTreeFactory factory_;
    std::unique_ptr<BT::Tree> tree_;
    std::unique_ptr<BT::Groot2Publisher> groot_publisher_;
    BT::Blackboard::Ptr blackboard_;

    // Shared state written by subscriptions, read by BT nodes via blackboard
    std::mutex detections_mutex_;
    std::vector<std::string> detected_objects_;
    bool battery_ok_ = true;
    geometry_msgs::msg::Pose current_pose_;
    std::mutex pose_mutex_;

    // Parameters
    std::string tree_file_;
};

}  // namespace mission_executive
