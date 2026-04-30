#pragma once
#include "behaviortree_ros2/bt_action_node.hpp"
#include "custom_interfaces/action/distance_trick.hpp"
#include "custom_interfaces/msg/pose6_d.hpp"
#include <string>

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
        std::chrono::steady_clock::time_point start_time;
        double timeout_sec;
        // std::string objectID;
        

}