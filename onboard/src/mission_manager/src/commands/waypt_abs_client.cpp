#include "include/commands/waypt_abs.hpp"

using namespace BT;

namespace CycloneCommands {
    WayptAbs::WayptAbs(const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<WayptAbs>(name, conf, params) {
        startTime = std::chrono::steady_clock::now();
        feedback_.delta = {0, 0, 0, 0, 0, 0};
        feedback_.time_in_tolerance = 0;
    }

    bool WayptAbs::setGoal(RosActionNode::Goal& goal) override {
        // get "order" from the Input port
        getInput("order", goal.order);
        // return true, if we were able to set the goal correctly.
        return true;
    }

    NodeStatus WayptAbs::onResultReceived (const WrappedResult& result) override {
        switch (result.result) {
            case "RUNNING":
                return NodeStatus::RUNNING;
            case "SUCCESS":
                return NodeStatus::SUCCESS;
        }
    }

    static PortsList providedPorts() {
        return { InputPort<float64[]>("tolerance") };
    }
    NodeStatus WayptAbs::tick() override  {
        /*
        CODE IS WRONG PROBABLY
        // check whether the robot is within tolerance
        // extract waypoint and hold time from goal
        auto goal_msg = WayptAbs::Goal();
        float64[6] waypt_t = goal_msg->waypoint;
        auto mask = goal_msg->waypoint_mask;
        float64 hold_time = goal_msg->hold_time;

        // get tolerance from blackboard, not sure
        auto msg = getInput<float64[]>("tolerance");
        if (!msg) {
            throw BT::RuntimeError("missing required input [tolerance]: ", msg.error() );
        }
        float64[6] tolerance = msg.value();

        bool startTolerance = false;
        while (true) {
            for (int i = 0; i < 6; i++) {
                if (mask[i]) {
                    if ((waypt_t[i] - tolerance[i] > currentPos[i]) || (currentPos[i] > waypt_t[i] + tolerance[i])) {
                        // not in tolerance for state ith
                        if (isInTolerance) {
                            isInTolerance = false;
                            startTime = std::chrono::steady_clock::now();
                        }     
                        break;               
                    }
                    if (!startTolerance) {
                        startTolerance = True;
                    }
                }
            }
            if (startTolerance && (!isInTolerance)) {
                // now in tolerance for the first time / exited out of tolerance
                startTime = std::chrono::steady_clock::now();
                isInTolerance = true;
                startTolerance = false;
            } else if ((isInTolerance)) {
                // measure how long it's been in tolerance
                currentTime = std::chrono::steady_clock::now();
                if ((currentTime - startTime) >= hold_time) {
                    return NodeStatus::SUCCESS;
                } else {
                    return NodeStatus::RUNNING;
                }
            } else {
                return NodeStatus::RUNNING;
            }
        }   
            */
    }
    NodeStatus WayptAbs::onFeedback(const std::shared_ptr<const Feedback> feedback) override {
        for (auto num : feedback->delta) {
            std::cout << num << " ";
        }
        std::cout << "\n";
        std::cout << feedback->time_in_tolerance << "\n";
        return NodeStatus::RUNNING;
    }
    
}
