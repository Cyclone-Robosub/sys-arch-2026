#include "server/custom_logger.hpp"

using namespace BT;

CustomLogger::CustomLogger(const Tree& tree, std::shared_ptr<rclcpp::Node> node)
  : RosLogger(tree, node)
{}

void CustomLogger::callback(Duration timestamp, const TreeNode& node, NodeStatus prev_status, NodeStatus status)
{
  (void) timestamp;
  // check if Node is a new subtree
  if ((((node.name() == "GateTask") || (node.name() == "Bins") || (node.name() == "Slalom") ||
        (node.name() == "Octagon") || (node.name() == "ReturnToGateTask") || (node.name() == "DropperTask"))) &&
      (status == BT::NodeStatus::RUNNING)) {
    current_mission_.subtree = node.name();
    current_mission_.status = status;
    progress_dirty_ = true;
  }
  // Check if Node is a leaf
  if (node.type() == BT::NodeType::ACTION || node.type() == BT::NodeType::CONDITION)
  {
    // new node starts running
    if (status == BT::NodeStatus::RUNNING)
    {
      current_mission_.command = node.name();
      current_mission_.status = status;
      progress_dirty_ = true;
      return;
    }
    // current node finishes execution
    if ((node.name() == current_mission_.command) && (prev_status == BT::NodeStatus::RUNNING) &&
        (status == BT::NodeStatus::SUCCESS || status == BT::NodeStatus::FAILURE))
    {
      current_mission_.status = status;
      progress_dirty_ = false;
    }
  }

}
