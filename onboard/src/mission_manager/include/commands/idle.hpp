#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/idle.hpp"

using namespace BT;

namespace CycloneCommands {
    class Idle : public RosActionNode<custom_interfaces::action::Idle> {
        public:
            Idle(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
            static PortsList providedPorts();
            bool setGoal(Goal& goal) override;
            NodeStatus onResultReceived(const WrappedResult& wr) override;
            void onhalt();
    };
}