#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/waypoint.hpp"
#include "custom_interfaces/msg/pose6_d.hpp"
#include "custom_interfaces/msg/waypoint_mask.hpp"
#include <string>

namespace CycloneCommands {
    using BT::NodeStatus;
    using BT::PortsList;
    using BT::RosActionNode;
    using BT::NodeConfig;
    using BT::RosNodeParams;
    using BT::ActionNodeErrorCode;
    using BT::InputPort;
    using BT::OutputPort;

    using Pose6D = custom_interfaces::msg::Pose6D;
    using WaypointMask = custom_interfaces::msg::WaypointMask;
}
