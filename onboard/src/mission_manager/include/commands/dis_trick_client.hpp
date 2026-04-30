#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/distance_trick.hpp"
#include "custom_interfaces/msg/pose6_d.hpp"
#include <string>

using namespace BT;
class DisTrick : public RosActionNode<DisTrick> {
    public:
        DisTrick(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        NodeStatus tick() override;
        bool setGoal(RosActionNode::Goal& goal) override;
        static PortsList providedPorts();
        NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback);
    private:
        std::chrono::steady_clock::time_point startTime;
        double timeout_sec;
}