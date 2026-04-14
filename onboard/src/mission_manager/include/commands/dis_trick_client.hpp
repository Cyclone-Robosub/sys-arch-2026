#include <behaviortree_ros2/bt_action_node.hpp>
#include <chrono>
using namespace BT;
class DisTrick : public RosActionNode<DisTrick> {
    public:
        DisTrick(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        NodeStatus tick() override;
        bool setGoal(RosActionNode::Goal& goal) override;
        static PortsList providedPorts();
    private:
        float64[6] currentPos;
        float64 startTime;
        float64 currentTime;
        bool isInTolerance = false;
}