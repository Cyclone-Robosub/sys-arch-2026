#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/dropper.hpp"
#include "command_alias.hpp"

namespace CycloneCommands {
    using Dropper= custom_interfaces::action::Dropper;
    class DropperCmd: public RosActionNode<Dropper> {
        public:
            DropperCmd(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
            NodeStatus tick() override;
            bool setGoal(Goal& goal) override;
            NodeStatus onResultReceived(const WrappedResult& wr) override;
            static PortsList providedPorts();
        private:
            std::chrono::steady_clock::time_point start_time;
            double timeout_sec;
    };

}