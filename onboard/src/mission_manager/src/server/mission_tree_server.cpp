#include "server/mission_tree_server.hpp"

#include "commands/idle.hpp"
#include "commands/waypoint.hpp"
#include "commands/seek_object.hpp"
#include "commands/object_rel_waypoint.hpp"
#include "commands/dis_trick_client.hpp"
#include "commands/duration_trick_client.hpp"

MissionTreeServer::MissionTreeServer(const rclcpp::NodeOptions& options) : TreeExecutionServer(options) {
    current_command_publisher = node()->create_publisher<custom_interfaces::msg::CommandTree>("current_command", 10);

}

void MissionTreeServer::onTreeCreated(BT::Tree& tree) {
    logger_cout_ = std::make_shared<CustomLogger>(tree, node());
}

std::optional<BT::NodeStatus> MissionTreeServer::onLoopAfterTick(BT::NodeStatus status) {
    (void) status;
    if (logger_cout_ && logger_cout_->isProgressDirty()) {
        // publish message with current subtree, command, and status
        auto report = custom_interfaces::msg::CommandTree();
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
   /*
    factory.registerSimpleAction("IdleDummyAction", [](BT::TreeNode& self){
        std::cout << "IdleDummyAction substituting: "<< self.name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    });
    factory.registerSimpleAction("WaypointDummyAction", [](BT::TreeNode& self) {
        std::cout << "WaypointDummyAction substituting: "<< self.name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    });
    factory.registerSimpleAction("SeekDummyAction", [](BT::TreeNode& self) {
        std::cout << "IdleDummyAction substituting: "<< self.name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    });
    factory.registerSimpleAction("ObjRelDummyAction", [](BT::TreeNode& self) {
        std::cout << "WaypointDummyAction substituting: "<< self.name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    });
    factory.registerSimpleAction("DistanceDummyAction", [](BT::TreeNode& self) {
        std::cout << "WaypointDummyAction substituting: "<< self.name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    });
    factory.registerSimpleAction("DurationDummyAction", [](BT::TreeNode& self) {
        std::cout << "WaypointDummyAction substituting: "<< self.name() << std::endl;
        return BT::NodeStatus::SUCCESS;
    });

    factory.addSubstitutionRule("Idle", "IdleDummyAction");
    factory.addSubstitutionRule("DriveToWorldWaypoint", "WaypointDummyAction");
    factory.addSubstitutionRule("DriveToWorldWaypointSeeking", "SeekDummyAction");
    factory.addSubstitutionRule("TrackObjectWaypoint", "ObjRelDummyAction");
    factory.addSubstitutionRule("DistanceTrick", "DistanceDummyAction");
    factory.addSubstitutionRule("DurationTrick", "DurationDummyAction");
    */ 
    
    factory.registerNodeType<CycloneCommands::IdleCmd>("Idle",  RosNodeParams(node(), "/idle_service"));
    factory.registerNodeType<CycloneCommands::WaypointCmd>("DriveToWorldWaypoint", RosNodeParams(node(), "/waypoint_service"));
    factory.registerNodeType<CycloneCommands::SeekObjCmd>("DriveToWorldWaypointSeeking", RosNodeParams(node(), "/seek_object_service"));
    factory.registerNodeType<CycloneCommands::ObjRelWaypointCmd>("TrackObjectWaypoint", RosNodeParams(node(), "/obj_rel_waypoint_service"));
    factory.registerNodeType<CycloneCommands::DistanceTrickCmd>("DistanceTrick", RosNodeParams(node(), "/distance_trick_service"));
    factory.registerNodeType<CycloneCommands::DurationTrickCmd>("DurationTrick", RosNodeParams(node(), "/duration_trick_service"));

}





