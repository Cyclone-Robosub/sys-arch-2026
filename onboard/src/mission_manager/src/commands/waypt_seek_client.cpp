#include "include/commands/waypt_seek_client.hpp"

using namespace BT;

namespace CycloneCommands {
    WayptSeek::WayptSeek(const std::string& name, const NodeConfig& conf, const RosNodeParams& params){
        
    }

    NodeStatus WayptSeek::tick() override{
        // move based on server directive
        // call onFeedback
        // check if goal has been accomplished 
        // (i.e. found object with confidence)
    }

    bool WayptSeek::setGoal(RosActionNode::Goal& goal) override{

    }

    static WayptSeek::PortsList providedPorts(){

    }

    NodeStatus WayptSeek::onFeedback(const std::shared_ptr<GoalHandleWayptSeek> goal_handle){
        const auto goal = goal_handle->get_goal();
        auto feedback = std::make_shared_ptr<WayptSeek::Feedback>();
        // get the current position and subtract from goal waypoint
        // set feedback "delta" field to this value
        // publish feedback to goal_handle for server
    }

}