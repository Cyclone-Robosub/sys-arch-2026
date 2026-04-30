#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/duration_trick.hpp"
#include <string>
using namespace BT;
class DurationTrick : public RosActionNode<DurationTrick> {
    public:
        DurationTrick(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        NodeStatus tick() override;
        bool setGoal(RosActionNode::Goal& goal) override;
        static PortsList providedPorts();
}