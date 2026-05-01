#pragma once
#include "behaviortree_ros2/bt_ros_logger.hpp"

struct MissionFileReport {
    std::string subtree;
    std::string command;
    BT::NodeStatus status;
};

class CustomLogger : public BT::RosLogger {
    public:
        explicit CustomLogger(BT::Tree& tree);
        bool isProgressDirty() const { return progress_dirty_; }
        void clearProgressDirty() { progress_dirty_ = false;}
        MissionFileReport getCurrentMission() {return current_mission_;}
    private:
        void callback (BT::Duration timestamp, const BT::TreeNode& node, BT::NodeStatus prev_status, BT::NodeStatus status) override;
        MissionFileReport current_mission_;
        bool progress_dirty_ = false; 
};