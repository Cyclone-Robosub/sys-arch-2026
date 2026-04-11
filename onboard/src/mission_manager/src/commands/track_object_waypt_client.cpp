#include "include/commands/track_object_waypt_client.hpp"

using namespace BT;

namespace CycloneCommand {
    ObjectWaypt::ObjectWaypt( const std::string& name, const NodeConfig& conf, const RosNodeParams& params) : RosActionNode<ObjectWaypt>(name, conf, params) {
        startTime = std::chrono::steady_clock::now();
    }

    static BT::PortsList providedPorts() {
        return providedBasicPorts({ InputPort<float64[]>("tolerance") });
    }

    bool ObjectWaypt::setGoal(RosActionNode::Goal& goal) {
        // get "order" from the Input port
        getInput("order", goal.order); // change?
        return true;
    }

    // Based on the reply you may decide to return SUCCESS or FAILURE.
    NodeStatus onResultReceived(const WrappedResult& wr) override {

    }

    NodeStatus ObjectWaypt::tick() override {

    }

    NodeStatus ObjectWaypt::onFailure() {
        
    }


}