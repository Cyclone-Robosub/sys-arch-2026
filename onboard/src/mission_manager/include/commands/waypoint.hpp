#pragma once

#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/waypoint.hpp"
#include "custom_interfaces/msg/pose6_d.hpp"
#include "custom_interfaces/msg/waypoint_mask.hpp"
#include <string>
using namespace BT;
class WayptAbs : public RosActionNode<WayptAbs> {
    public:
        WayptAbs(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        static PortsList providedPorts();
        bool setGoal(RosActionNode::Goal& goal) override;
    private:
        std::chrono::steady_clock::time_point startTime;
        double timeout_sec;
}