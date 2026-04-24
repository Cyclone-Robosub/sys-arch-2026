#include "include/commands/waypt_seek_client.hpp"

using namespace BT;

namespace CycloneCommands {
    WayptSeek::WayptSeek(const std::string& name, const NodeConfig& conf, const RosNodeParams& params){
        
    }

    // NodeStatus WayptSeek::tick() override {
    //     NodeStatus status; // has to come from the server, i.e. the matlab side?
    //     if (status == NodeStatus::RUNNING) {
    //         if (now - start_time > timeout_sec) {
    //             return NodeStatus::FAILURE;
    //         }
    //     }
    // }
    NodeStatus WayptSeek::tick() {
        NodeStatus status = RosActionNode<cyclone_msgs::action::TrackObjectWaypt>::tick();

        if (status == NodeStatus::RUNNING) {
            std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
            double elapsed = std::chrono::duration<double>(now - start_time).count();
            if (elapsed > timeout_sec) {
                RCLCPP_ERROR(logger(), "Error: %d", error);
                return NodeStatus::FAILURE;
            }
        }

        return status;
        
    }

    bool WayptSeek::setGoal(RosActionNode::Goal& goal) override{
        // set attributes for the goal
        startTime = std::chrono::steady_clock::now();
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