#include "include/commands/track_object_waypt_client.hpp"

using namespace BT;
// I think track object waypt is pretty much the same as waypt abs
namespace CycloneCommand {
    ObjectWaypt::ObjectWaypt( const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<ObjectWaypt>(name, conf, params) {
        startTime = std::chrono::steady_clock::now();

        
    }

    static BT::PortsList providedPorts() {
        return { InputPort<float64[]>("tolerance"), InputPort<float64[]>("trackingPos"), 
        InputPort<bool[]>("waypointMask"), InputPort<std::string>("object"), InputPort<float64>("holdTime") };
    }

    bool ObjectWaypt::setGoal(RosActionNode::Goal& goal) {
        // get "order" from the Input port
        getInput("order", goal.order); // change?
        return true;
    }

    // Based on the reply you may decide to return SUCCESS or FAILURE.
    NodeStatus onResultReceived(const WrappedResult& wr) override {
        if () { 

            return NodeStatus::SUCCESS;
        }
    }

    NodeStatus ObjectWaypt::tick() override {
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
    }

    NodeStatus ObjectWaypt::onFailure() {
        
    }


}