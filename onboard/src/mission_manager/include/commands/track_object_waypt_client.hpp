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
        NodeStatus ObjectWaypt::onFailure(ActionNodeErrorCode error);
        NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback);

    
    private:
        double[6] currentPos;
        double startTime;
        double currentTime;
        bool isInTolerance = false;
        std::string objectID;
        

}