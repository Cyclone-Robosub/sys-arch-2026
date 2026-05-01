#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/idle.hpp"
#include "command_alias.hpp"


namespace CycloneCommands {
    class IdleCmd : public RosActionNode<custom_interfaces::action::Idle> {
        public:
            IdleCmd(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
            static PortsList providedPorts();
            bool setGoal(Goal& goal) override;
            NodeStatus onResultReceived (const WrappedResult& result) override;
            void onHalt() override;
    };
}