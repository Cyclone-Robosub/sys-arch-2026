#pragma once

#include "behaviortree_ros2/bt_action_node.hpp"
#include "command_alias.hpp"
#include "custom_interfaces/action/waypoint.hpp"
#include <string>

namespace CycloneCommands {
    using Waypoint = custom_interfaces::action::Waypoint;
    class WaypointCmd : public RosActionNode<Waypoint> {
        public:
            WaypointCmd(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
            static PortsList providedPorts();
            bool setGoal(Goal& goal) override;
            NodeStatus onResultReceived(const WrappedResult& result) override;
    };
}