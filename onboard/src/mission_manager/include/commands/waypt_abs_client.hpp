#include <chrono>
using namespace BT;
class WayptAbs : public RosActionNode<WayptAbs> {
    public:
        WayptAbs(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        NodeStatus tick() override;
        bool setGoal(RosActionNode::Goal& goal) override;
        static PortsList providedPorts();
    private:
        float64[6] currentPos;
        float64 startTime;
        float64 currentTime;
        bool isInTolerance = false;
}