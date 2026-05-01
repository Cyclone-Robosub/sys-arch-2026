#include "server/mission_tree_server.hpp"
#include "custom_interfaces/action/idle.hpp"
#include "custom_interfaces/action/waypoint.hpp"
#include "custom_interfaces/action/seek_object.hpp"
#include "custom_interfaces/action/object_relative_waypoint.hpp"
#include "custom_interfaces/action/distance_trick.hpp"
#include "custom_interfaces/action/duration_trick.hpp"

using Idle = custom_interfaces::action::Idle;
using Waypoint = custom_interfaces::action::Waypoint;
using SeekObj = custom_interfaces::action::SeekObject;
using ObjRelWaypoint = custom_interfaces::action::ObjectRelativeWaypoint;
using DisTrick = custom_interfaces::action::DistanceTrick;
using DurTrick = custom_interfaces::action::DurationTrick;

MissionTreeServer::MissionTreeServer(const rclcpp::NodeOptions& options) : TreeExecutionServer(options) {}

void MissionTreeServer::onTreeCreated(BT::Tree& tree) {
    logger_cout_ = std::make_shared<CustomLogger>(tree);
}

std::optional<BT::NodeStatus> MissionTreeServer::onLoopAfterTick(BT::NodeStatus status) {
    if (progress_dirty_) {
        // publish message with current subtree, command, and status
        progress_dirty_ = false;
    }
    return std::nullopt;
}

void MissionTreeServer::registerNodesIntoFactory (BT::BehaviorTreeFactory& factory) {
    factory.registerNodeType<Idle>("Idle",  BT::RosNodeParams(node(), "/idle"));
    factory.registerNodeType<Waypoint>("DriveToWorldWaypoint", BT::RosNodeParams(node(), "/waypt_abs"));
    factory.registerNodeType<SeekObj>("DriveToWorldWaypointSeeking", BT::RosNodeParams(node(), "/waypt_seek"));
    factory.registerNodeType<ObjRelWaypoint>("TrackObjectWaypoint", BT::RosNodeParams(node(), "/waypt_fix"));
    factory.registerNodeType<DisTrick>("DistanceTrick", BT::RosNodeParams(node(), "/trick_dis"));                
    factory.registerNodeType<DurTrick>("DurationTrick", BT::RosNodeParams(node(), "/trick_timed"));
}
