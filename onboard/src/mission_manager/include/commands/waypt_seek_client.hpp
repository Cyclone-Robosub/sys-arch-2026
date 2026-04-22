#include <chrono>
using namespace BT;
class WayptSeek : public RosActionNode<WayptSeek> {
    public:
        WayptSeek(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        NodeStatus tick() override;
        bool setGoal(RosActionNode::Goal& goal) override;
        static PortsList providedPorts();
        NodeStatus onFeedback(const std::shared_ptr<GoalHandleWayptSeek> goal_handle)
    private:
        float64[6] currentPos; // unsure as to whether this is necessary
        std::chrono::steady_clock::time_point startTime;
        bool isConfident = false; // unsure as to whether this is necessary
}