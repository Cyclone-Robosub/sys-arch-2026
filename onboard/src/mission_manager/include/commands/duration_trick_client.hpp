#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/duration_trick.hpp"
#include "command_alias.hpp"
#include <string>

namespace CycloneCommands {
    using DurationTrick = custom_interfaces::action::DurationTrick;

    class DurationTrickCmd : public RosActionNode<DurationTrick> {
    public:
        DurationTrickCmd(const std::string &name, const NodeConfig &conf, const BT::RosNodeParams &params);
        bool setGoal(Goal &goal) override;
        static PortsList providedPorts();
        NodeStatus onResultReceived(const WrappedResult &result) override;
    };
}
