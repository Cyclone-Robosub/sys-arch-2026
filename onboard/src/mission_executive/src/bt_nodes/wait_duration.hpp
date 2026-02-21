#pragma once

#include <behaviortree_cpp/action_node.h>
#include <chrono>
#include <optional>

class WaitDuration : public BT::StatefulActionNode {
public:
    WaitDuration(const std::string& name, const BT::NodeConfig& config)
        : StatefulActionNode(name, config) {}

    static BT::PortsList providedPorts() {
        return {
            BT::InputPort<double>("duration", "Duration to wait in seconds"),
        };
    }

    BT::NodeStatus onStart() override {
        auto duration = getInput<double>("duration");
        if (!duration) {
            throw BT::RuntimeError("WaitDuration: missing required 'duration' input");
        }
        duration_sec_ = duration.value();
        start_time_ = std::chrono::steady_clock::now();
        return BT::NodeStatus::RUNNING;
    }

    BT::NodeStatus onRunning() override {
        auto elapsed = std::chrono::steady_clock::now() - start_time_;
        if (elapsed >= std::chrono::duration<double>(duration_sec_)) {
            return BT::NodeStatus::SUCCESS;
        }
        return BT::NodeStatus::RUNNING;
    }

    void onHalted() override {
        // Nothing to clean up
    }

private:
    double duration_sec_ = 0.0;
    std::chrono::steady_clock::time_point start_time_;
};
