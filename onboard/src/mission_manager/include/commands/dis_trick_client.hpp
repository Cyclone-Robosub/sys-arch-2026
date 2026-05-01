#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/distance_trick.hpp"
#include "command_alias.hpp"
#include <string>

namespace CycloneCommands {
    using DistanceTrick = custom_interfaces::action::DistanceTrick;
    
    class DistanceTrickCmd : public BT::RosActionNode<DistanceTrick> {
        public:
            DistanceTrickCmd(const std::string& name, const NodeConfig& conf, const BT::RosNodeParams& params);
            bool setGoal(Goal& goal) override;
            static PortsList providedPorts();
            NodeStatus onResultReceived (const WrappedResult& result) override;
        private:
            std::chrono::steady_clock::time_point startTime;
            double timeout_sec;
    };
}