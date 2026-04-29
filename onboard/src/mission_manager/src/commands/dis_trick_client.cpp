using namespace BT;

namespace CycloneCommands {
    DisTrick::DisTrick(const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<WayptAbs>(name, conf, params) 
    {}
    
    bool DisTrick::setGoal(RosActionNode::Goal& goal) override {
        getInput("waypoint", goal.waypoint);
        getInput("waypoint_mask", goal.waypoint_mask);
        getInput("hold_time", goal.hold_time);
        getInput("tolerance", goal.tolerance);
        // return true, if we were able to set the goal correctly.
        return true;
    }

    NodeStatus DisTrick::onResultReceived (const WrappedResult& result) override {
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
    NodeStatus DisTrick::tick() override  {
        /*
        // extract ...  from goal
        auto goal_msg = DisTrick::Goal();
        std::string trick = goal_msg->trick;
        auto duration = goal_msg->duration;
        auto mask = goal_msg->waypoint_mask;
        float64 hold_time = goal_msg->hold_time;
        
        // execute the trick
        while (std::chrono::steady_clock::now() - startTime <= duration) {
            std::cout << "executing trick " << trick << "\n";
        }
        // check whether the robot is within tolerance
        // get tolerance from blackboard, should be changed to service
        auto msg = getInput<float64[]>("tolerance");
        if (!msg) {
            throw BT::RuntimeError("missing required input [tolerance]: ", msg.error() );
        }
        float64[6] tolerance = msg.value();

        bool startTolerance = false;
        while (true) {
            for (int i = 0; i < 6; i++) {
                if (mask[i]) {
                    if ((ogPos[i] - tolerance[i] > currentPos[i]) || (currentPos[i] > ogPos[i] + tolerance[i])) {
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
    NodeStatus DisTrick::onFeedback(const std::shared_ptr<const Feedback> feedback) override {
        for (auto num : feedback->current_pose) {
            std::cout << num << " ";
        }
        std::cout << "\n";
        std::cout << feedback->time_in_tolerance << "\n";
        return NodeStatus::RUNNING;
    }

}