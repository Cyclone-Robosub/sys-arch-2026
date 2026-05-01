#include "server/custom_logger.hpp"

using namespace BT;

void CustomLogger::callback (Duration timestamp, const TreeNode& node, NodeStatus prev_status, NodeStatus status) {
    // check if Node is a new subtree
    if ((((node.name() == "Gate Task") || (node.name() == "Bins") || (node.name() == "Slalom") || (node.name() == "Octagon") || (node.name() == "Return to Gate"))) && (status == BT::NodeStatus::RUNNING)) {
        current_mission.subtree = node.name();
        current_mission.status = status;
        progress_dirty_ = true;
    }
    // Check if Node is a leaf
    if (node->type() == BT::NodeType::ACTION || node->type() == BT::NodeType::CONDITION) {
        // new node starts running
        if (status == BT::NodeStatus::RUNNING) {
            current_mission.name = node.name();
            current_mission.status = status;
            progress_dirty_ = true;
            return;
        }
        // current node finishes execution 
        if ((node.name() == current_mission.name) && (prev_status == BT::NodeStatus::RUNNING) && (status == BT::NodeStatus::SUCCESS || status == BT::NodeStatus::FAILURE)) {
            current_mission.status = status;
            progress_dirty_ = false;
        }
    }
}
