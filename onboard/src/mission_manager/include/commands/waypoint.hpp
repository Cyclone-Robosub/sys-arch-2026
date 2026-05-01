#pragma once

#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/waypoint.hpp"
#include "custom_interfaces/msg/pose6_d.hpp"
#include "custom_interfaces/msg/waypoint_mask.hpp"
#include <string>

namespace CycloneCommands {
    class Waypoint : public BT::RosActionNode<custom_interfaces::action::Waypoint> {
        public:
            Waypoint(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
            static BT::PortsList providedPorts();
            bool setGoal(RosActionNode::Goal& goal) override;
            BT::NodeStatus Waypoint::onResultReceived(const WrappedResult& result) override;
        private:
            std::chrono::steady_clock::time_point startTime;
            double timeout_sec;
    };
}