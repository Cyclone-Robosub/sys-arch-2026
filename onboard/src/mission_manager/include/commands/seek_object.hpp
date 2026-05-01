#pragma once
#include "command_alias.hpp"
#include "custom_interfaces/action/seek_object.hpp"
#include <string>

namespace CycloneCommands {
    using SeekObject = custom_interfaces::action::SeekObject;
    class SeekObjCmd : public RosActionNode<SeekObject> {
        public:
            SeekObjCmd(const std::string& name, const NodeConfig& conf, const RosNodeParams& params);
            static PortsList providedPorts();
            bool setGoal(Goal& goal) override;
            NodeStatus onResultReceived(const WrappedResult& result) override;
    };
}