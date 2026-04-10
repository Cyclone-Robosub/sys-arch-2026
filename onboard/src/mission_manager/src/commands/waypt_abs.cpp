#include "include/commands/waypt_abs.hpp"

using namespace BT;

namespace CycloneCommands {

class WayptAbs : public RosActionNode<WayptAbs> {
    public:
        WayptAbs(const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<Fibonacci>(name, conf, params) {
            startTime = std::chrono::steady_clock::now();

        }

        bool setGoal(RosActionNode::Goal& goal) override {
            // get "order" from the Input port
            getInput("order", goal.order);
            // return true, if we were able to set the goal correctly.
            return true;
        }
        BT::NodeStatus tick() override  {
            // check whether the robot is within tolerance

            // Extract goal
            auto goal_msg = WayptAbs::Goal();
            float64[6] waypt_t = goal_msg->waypoint;

            // check tolerance
            float64[6] tolerance = goal_msg->tolerance;
            for (int i = 0; i < 6; i++) {
                if ((waypt_t[i] - tolerance[i] > currentPos[i]) || (currentPos[i] > waypt_t[i] + tolerance[i])) {
                    // not in tolerance for state ith
                    if (isInTolerance) {
                        
                        isInTolerance = false;
                    }                    
                    break;
                }
                if ((i == 5) && (!isInTolerance)) {
                    // now in tolerance for the first time
                    startTime = std::chrono::steady_clock::now();
                    isInTolerance = true;
                }
            }
             
            

            return BT::NodeStatus::SUCCESS;
        }

    private:
}
}