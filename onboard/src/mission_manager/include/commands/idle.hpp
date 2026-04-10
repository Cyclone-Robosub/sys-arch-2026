#include <behaviortree_ros2/bt_action_node.hpp>
#include "custom_interfaces/action/idle.hpp"

using idle = custom_interfaces::action::idle;

namespace CycloneCommand {
    class Idle : public RosActionNode<idle>;
}