#include "behaviortree_ros2/bt_ros_logger.hpp"
using namespace BT;
class CustomLogger : public RosLogger {
    void callback (Duration timestamp, const TreeNode& node, NodeStatus prev_status, NodeStatus status) override {
        // Check if Node is a leaf
        if (node->type() == BT::NodeType::ACTION || node->type() == BT::NodeType::CONDITION) {
            if (status == BT::NodeStatus::RUNNING) {
                current_command_name_ = node.name();
                current_command_status_ = status;
                progress_dirty_ = true;
                return;
            }

            if (node.name() == current_command_name_ && prev_status == BT::NodeStatus::RUNNING && (status == BT::NodeStatus::SUCCESS || status == BT::NodeStatus::FAILURE)) {
                current_command_status_ = status;
                progress_dirty_ = true;
            }
        }
    }
}