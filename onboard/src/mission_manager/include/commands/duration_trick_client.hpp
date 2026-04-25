#include <behaviortree_ros2/bt_action_node.hpp>
#include <chrono>
using namespace BT;
class DurationTrick : public RosActionNode<DurationTrick> {
    public:
        DurationTrick(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        NodeStatus tick() override;
        bool setGoal(RosActionNode::Goal& goal) override;
        static PortsList providedPorts();
        NodeStatus onFeedback(const std::shared_ptr<GoalHandleWayptSeek> goal_handle);
    private:
        std::chrono::steady_clock::time_point startTime;
        double timeout_sec;
}