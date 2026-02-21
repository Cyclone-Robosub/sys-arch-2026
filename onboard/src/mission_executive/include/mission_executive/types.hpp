#pragma once

#include <behaviortree_cpp/bt_factory.h>
#include <string>

namespace mission_executive {

enum class VisionTarget {
    GATE,
    BINS,
    BUOY,
    TORPEDO_TARGET,
    OCTAGON
};

enum class ManipulatorCommand {
    OPEN = 0,
    CLOSE = 1,
    RELEASE = 2
};

inline std::string toString(VisionTarget target) {
    switch (target) {
        case VisionTarget::GATE: return "GATE";
        case VisionTarget::BINS: return "BINS";
        case VisionTarget::BUOY: return "BUOY";
        case VisionTarget::TORPEDO_TARGET: return "TORPEDO_TARGET";
        case VisionTarget::OCTAGON: return "OCTAGON";
    }
    return "UNKNOWN";
}

inline std::string toString(ManipulatorCommand cmd) {
    switch (cmd) {
        case ManipulatorCommand::OPEN: return "OPEN";
        case ManipulatorCommand::CLOSE: return "CLOSE";
        case ManipulatorCommand::RELEASE: return "RELEASE";
    }
    return "UNKNOWN";
}

}  // namespace mission_executive

namespace BT {

template<>
inline mission_executive::VisionTarget convertFromString(StringView str) {
    if (str == "GATE") return mission_executive::VisionTarget::GATE;
    if (str == "BINS") return mission_executive::VisionTarget::BINS;
    if (str == "BUOY") return mission_executive::VisionTarget::BUOY;
    if (str == "TORPEDO_TARGET") return mission_executive::VisionTarget::TORPEDO_TARGET;
    if (str == "OCTAGON") return mission_executive::VisionTarget::OCTAGON;
    throw RuntimeError("invalid VisionTarget: " + std::string(str));
}

template<>
inline mission_executive::ManipulatorCommand convertFromString(StringView str) {
    if (str == "OPEN") return mission_executive::ManipulatorCommand::OPEN;
    if (str == "CLOSE") return mission_executive::ManipulatorCommand::CLOSE;
    if (str == "RELEASE") return mission_executive::ManipulatorCommand::RELEASE;
    throw RuntimeError("invalid ManipulatorCommand: " + std::string(str));
}

}  // namespace BT
