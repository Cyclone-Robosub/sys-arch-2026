#include "server/mission_tree_server.hpp"

#include "commands/idle.hpp"
#include "commands/waypoint.hpp"
#include "commands/seek_object.hpp"
#include "commands/object_rel_waypoint.hpp"
#include "commands/dis_trick_client.hpp"
#include "commands/duration_trick_client.hpp"

MissionTreeServer::MissionTreeServer(const rclcpp::NodeOptions& options) : TreeExecutionServer(options) {}

void MissionTreeServer::onTreeCreated(BT::Tree& tree) {
    logger_cout_ = std::make_shared<CustomLogger>(tree, node());
}

std::optional<BT::NodeStatus> MissionTreeServer::onLoopAfterTick(BT::NodeStatus status) {
    (void) status;
    if (logger_cout_ && logger_cout_->isProgressDirty()) {
        // publish message with current subtree, command, and status
        logger_cout_->clearProgressDirty();
    }
    return std::nullopt;
}

void MissionTreeServer::registerNodesIntoFactory (BT::BehaviorTreeFactory& factory) {
    factory.registerNodeType<CycloneCommands::IdleCmd>("Idle",  RosNodeParams(node(), "/idle"));
    factory.registerNodeType<CycloneCommands::WaypointCmd>("DriveToWorldWaypoint", RosNodeParams(node(), "/waypt_abs"));
    factory.registerNodeType<CycloneCommands::SeekObjCmd>("DriveToWorldWaypointSeeking", RosNodeParams(node(), "/waypt_seek"));
    factory.registerNodeType<CycloneCommands::ObjRelWaypointCmd>("TrackObjectWaypoint", RosNodeParams(node(), "/waypt_fix"));
    factory.registerNodeType<CycloneCommands::DistanceTrickCmd>("DistanceTrick", RosNodeParams(node(), "/trick_dis"));                
    factory.registerNodeType<CycloneCommands::DurationTrickCmd>("DurationTrick", RosNodeParams(node(), "/trick_timed"));
}
