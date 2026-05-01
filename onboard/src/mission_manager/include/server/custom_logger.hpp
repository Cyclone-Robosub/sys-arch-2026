#include "behaviortree_ros2/bt_ros_logger.hpp"
using namespace BT;

class CustomLogger : public RosLogger {
    void callback (Duration timestamp, const TreeNode& node, NodeStatus prev_status, NodeStatus status) override; 
};