#include "server/mission_tree_server.hpp"

#include "commands/idle.hpp"
#include "commands/waypoint.hpp"
#include "commands/seek_object.hpp"
#include "commands/object_rel_waypoint.hpp"
#include "commands/dis_trick_client.hpp"
#include "commands/duration_trick_client.hpp"

MissionTreeServer::MissionTreeServer(const rclcpp::NodeOptions& options) : TreeExecutionServer(options) {
    current_command_publisher = node()->create_publisher<custom_interfaces::msg::Command>("current_command", 10);
}

void MissionTreeServer::onTreeCreated(BT::Tree& tree) {
    logger_cout_ = std::make_shared<CustomLogger>(tree, node());
}

std::optional<BT::NodeStatus> MissionTreeServer::onLoopAfterTick(BT::NodeStatus status) {
    (void) status;
    if (logger_cout_ && logger_cout_->isProgressDirty()) {
        // publish message with current subtree, command, and status
        auto report = custom_interfaces::msg::Command();
        auto current_mission_ = logger_cout_->getCurrentMission();
        report.current_subtree = current_mission_.subtree;
        report.current_command = current_mission_.command;
        report.status = "FAILURE";
        if (current_mission_.status == BT::NodeStatus::RUNNING) {
            report.status = "RUNNING";
        } else if (current_mission_.status == BT::NodeStatus::SUCCESS) {
            report.status = "SUCCESS";
        }
        current_command_publisher->publish(report);
        // resets logger
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


// sam
void MissionTreeServer::ctrl_heartbeat_callback(std_msgs::msg::Empty::UniquePtr heartbeat) {}

void MissionTreeServer::heartbeat_callback() {
    mux_heartbeat_send();
    ctrl_heartbeat_check();
    cli_heartbeat_check();
    echo_heartbeat_check();
    publish_stop_if_disabled();
}

void MissionTreeServer::heartbeat_callback() {}

void MissionTreeServer::ctrl_heartbeat_check() {}

void MissionTreeServer::cli_heartbeat_callback(std_msgs::msg::Empty::UniquePtr heartbeat){}

void MissionTreeServer::echo_heartbeat_check() {}

void MissionTreeServer::echo_heartbeat_callback(std_msgs::msg::Empty::UniquePtr heartbeat){}

void MissionTreeServer::cli_heartbeat_check() {}

void MissionTreeServer::mux_heartbeat_send() {}

