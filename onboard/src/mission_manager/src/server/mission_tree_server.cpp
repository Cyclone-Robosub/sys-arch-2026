#include "include/server/mission_tree.hpp"
void MissionTreeServer::onTreeCreated(BT::Tree& tree) override {
    logger_cout_ = std::make_shared<CustomLogger>(tree);

}

std::optional<std::string> MissionTreeServer::onLoopFeedback() override{
    return current_command;
}

void MissionTreeServer::registerNodesIntoFactory (BT::BehaviorTreeFactory& factory) override {
    factory.registerNodeType<Idle>("Idle",  BT::RosNodeParams(node(), "/idle"));
    factory.registerNodeType<WayptAbs>("DriveToWorldWaypoint", BT::RosNodeParams(node(), "/waypt_abs"));
    factory.registerNodeType<WayptSeek>("DriveToWorldWaypointSeeking", BT::RosNodeParams(node(), "/waypt_seek"));
    factory.registerNodeType<TrackObjectWaypoint>("TrackObjectWaypoint", BT::RosNodeParams(node(), "/waypt_fix"));
    factory.registerNodeType<DistanceTrick>("DistanceTrick", BT::RosNodeParams(node(), "/trick_dis"));                
    factory.registerNodeType<DurationTrick>("DurationTrick", BT::RosNodeParams(node(), "/trick_timed"));
}
