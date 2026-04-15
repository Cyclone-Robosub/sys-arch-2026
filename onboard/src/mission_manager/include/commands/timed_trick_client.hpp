#include <behaviortree_ros2/bt_action_node.hpp>
#include <chrono>
using namespace BT;
class TimedTrick : public RosActionNode<TimedTrick> {
    public:
        TimedTrick(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        NodeStatus tick() override;
        bool setGoal(RosActionNode::Goal& goal) override;
        static PortsList providedPorts();
        NodeStatus onFeedback(const std::shared_ptr<GoalHandleWayptSeek> goal_handle);
    private:
        float64[6] ogPos;
        float64[6] currentPos;
        float64 startTime;
        float64 currentTime;
        bool isInTolerance = false;
}