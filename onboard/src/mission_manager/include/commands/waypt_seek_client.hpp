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
        float64[6] currentPos;
        float64 startTime;
        float64 currentTime;
        bool isConfident = false;
}