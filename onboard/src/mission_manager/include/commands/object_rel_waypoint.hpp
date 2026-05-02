#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/object_relative_waypoint.hpp"
#include "command_alias.hpp"
#include <string>

namespace CycloneCommands {
    using ObjectRelWaypoint = custom_interfaces::action::ObjectRelativeWaypoint;
    class ObjRelWaypointCmd: public RosActionNode<ObjectRelWaypoint> {
        public:
            ObjRelWaypointCmd(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
            NodeStatus tick() override;
            bool setGoal(Goal& goal) override;
            NodeStatus onResultReceived(const WrappedResult& wr) override;
            static PortsList providedPorts();
        private:
            std::chrono::steady_clock::time_point start_time;
            double timeout_sec;
    };

}