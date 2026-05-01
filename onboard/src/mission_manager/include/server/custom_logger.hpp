#include "behaviortree_ros2/bt_ros_logger.hpp"
using namespace BT;


struct mission_file_report {
    std::string subtree;
    std::string command;
    std::string status;
};

class CustomLogger : public RosLogger {
    void callback (Duration timestamp, const TreeNode& node, NodeStatus prev_status, NodeStatus status) override;
    mission_file_report current_mission;
    bool progress_dirty_; 
};