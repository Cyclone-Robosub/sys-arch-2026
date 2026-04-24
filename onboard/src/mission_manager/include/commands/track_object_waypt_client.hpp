#include <behaviortree_ros2/bt_action_node.hpp>
#include <chrono>

using namespace BT;
class ObjectWaypt: public RosActionNode<ObjectWaypt> {
    public:
        ObjectWaypt(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
        // NodeStatus tick() override;
        bool setGoal(RosActionNode::Goal& goal) override;
        NodeStatus onResultReceived(const WrappedResult& wr) override;
        static PortsList providedPorts();
        NodeStatus onFailure(ActionNodeErrorCode error) override;
        NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback) override;
        NodeStatus tick() override;

    
    private:
        // double[6] currentPos;
        std::chrono::steady_clock::time_point start_time;
        // double currentTime;
        bool isInTolerance = false;
        double timeout_sec;
        // std::string objectID;
        

}