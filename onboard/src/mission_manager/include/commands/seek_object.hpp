#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/seek_object.hpp"
#include "custom_interfaces/msg/pose6_d.hpp"
#include <string>
using namespace BT;

class WayptSeek : public RosActionNode<custom_interfaces::action::SeekObject> {
    public:
        WayptSeek(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        static PortsList providedPorts();
        bool setGoal(RosActionNode::Goal& goal) override;
};