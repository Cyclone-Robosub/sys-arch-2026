#include "command_alias.hpp"
using namespace CycloneCommands;

namespace BT {
    template<> inline Pose6D convertFromString(StringView key) {
        auto parts = BT::splitString(key, ',');
        if (parts.size() != 6) {
            throw BT::RuntimeError("invalid input");
        } else {
            Pose6D output;
            output.x = convertFromString<double>(parts[0]);
            output.y = convertFromString<double>(parts[1]);
            output.z = convertFromString<double>(parts[2]);
            output.roll = convertFromString<double>(parts[3]);
            output.pitch = convertFromString<double>(parts[4]);
            output.yaw = convertFromString<double>(parts[5]);
            return output;
        }
    }
    template<> inline WaypointMask convertFromString(StringView key) {
        auto parts = BT::splitString(key, ',');
        if (parts.size() != 6) {
            throw BT::RuntimeError("invalid input");
        } else {
            WaypointMask output;
            output.x = convertFromString<bool>(parts[0]);
            output.y = convertFromString<bool>(parts[1]);
            output.z = convertFromString<bool>(parts[2]);
            output.roll = convertFromString<bool>(parts[3]);
            output.pitch = convertFromString<bool>(parts[4]);
            output.yaw = convertFromString<bool>(parts[5]);
            return output;
        }
    }
}