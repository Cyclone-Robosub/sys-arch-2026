#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/duration_trick.hpp"
#include <string>
using namespace BT;

namespace CycloneCommands {
    class DurationTrick : public RosActionNode<custom_interfaces::action::DurationTrick> {
        public:
            DurationTrick(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
            NodeStatus tick() override;
            bool setGoal(RosActionNode::Goal& goal) override;
            static PortsList providedPorts();
    };
}