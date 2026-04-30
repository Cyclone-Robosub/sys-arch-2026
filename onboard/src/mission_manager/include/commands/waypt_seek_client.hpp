#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/SeekObject.hpp"
#include "custom_interfaces/msg/pose6_d.hpp"
#include <string>
using namespace BT;
class WayptSeek : public RosActionNode<WayptSeek> {
    public:
        WayptSeek(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        static PortsList providedPorts();
        bool setGoal(RosActionNode::Goal& goal) override;
}