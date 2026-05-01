#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/seek_object.hpp"
#include "custom_interfaces/msg/pose6_d.hpp"
#include <string>

namespace CycloneCommands {
    class SeekObj : public BT::RosActionNode<custom_interfaces::action::SeekObject> {
        public:
            explicit SeekObj(const std::string& name, const BT::NodeConfig& conf, const BT::RosNodeParams& params);
            static BT::PortsList providedPorts();
            bool setGoal(BT::RosActionNode::Goal& goal) override;
    };
}