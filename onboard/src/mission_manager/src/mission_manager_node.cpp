#include "mission_manager_node.hpp"
using namespace std::chrono_literals;

MissionManagerNode::MissionManagerNode() : rclcpp::Node("mission_manager") {
  ready_service =  this->create_service<std_srvs::srv::Trigger>("ready_signal_service", std::bind(&MissionManagerNode::trigger_ready_signal, this, std::placeholders::_1, std::placeholders::_2));
  execute_tree_client = rclcpp_action::create_client<ExecuteTree>(this, "bt_action_server");
  go_signal_subscriber = this->create_subscription<std_msgs::msg::Bool>("go_signal", 10, std::bind(&MissionManagerNode::go_signal_callback, this, std::placeholders::_1));
  heartbeat_timer = this->create_wall_timer(500ms, std::bind(&MissionManagerNode::heartbeat_callback, this));
  mission_manager_heartbeat_publisher = this->create_publisher<std_msgs::msg::Empty>("mission_manager_heartbeat", 10);
}


/*
    get trigger from website (ready signal)
*/
void MissionManagerNode::trigger_ready_signal(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
    (void) request;
    ready_signal = !ready_signal;
    response->success = true;
}

/*
    listens to the go_signal topic and gets go switch state
*/
void MissionManagerNode::go_signal_callback(std_msgs::msg::Bool::SharedPtr signal) {
    go_signal = signal->data;
    try_start_mission();
}

/*
    if we are primed (ready) and get go signal (go switch has been triggered), start run by sending the goal (the mission file) to MissionTreeServer
*/
void MissionManagerNode::try_start_mission() {
   if (!ready_signal || !go_signal || mission_started) {
        return;
   }
   ExecuteTree::Goal goal;
   goal.target_tree = "TrialTree";
   mission_started = true;
   execute_tree_client->async_send_goal(goal);
}

/*
    Heartbeat functions
*/
void MissionManagerNode::heartbeat_callback() {
    mission_manager_heartbeat_send();
}

void MissionManagerNode::mission_manager_heartbeat_send() {
    std_msgs::msg::Empty msg;
    this->mission_manager_heartbeat_publisher->publish(msg);
}


/*
    Creates MissionManagerNode to oversee the Server and start on conditions
    Creates MissionTreeServer object and spins
*/
#ifndef ENABLE_TESTING
int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
   
    rclcpp::NodeOptions options;
    auto action_server = std::make_shared<MissionTreeServer>(options);
    auto waypoint_action_server = std::make_shared<WaypointActionServer>();
    auto distance_trick_action_server = std::make_shared<DistanceTrickActionServer>();
    auto duration_trick_action_server = std::make_shared<DurationTrickActionServer>();
    auto idle_action_server = std::make_shared<IdleActionServer>();
    auto obj_rel_waypoint_action_server = std::make_shared<ObjRelWaypointActionServer>();
    auto seek_object_action_server = std::make_shared<SeekObjectActionServer>();
    auto mission_manager = std::make_shared<MissionManagerNode>();
    // TODO: This workaround is for a bug in MultiThreadedExecutor where it can deadlock when spinning without a timeout.
    // Deadlock is caused when Publishers or Subscribers are dynamically removed as the node is spinning.
    rclcpp::executors::MultiThreadedExecutor exec(rclcpp::ExecutorOptions(), 0, false,
                                                std::chrono::milliseconds(250));
    exec.add_node(action_server->node());
    exec.add_node(waypoint_action_server);
    exec.add_node(distance_trick_action_server);
    exec.add_node(duration_trick_action_server);
    exec.add_node(idle_action_server);
    exec.add_node(obj_rel_waypoint_action_server);
    exec.add_node(seek_object_action_server);
    exec.add_node(mission_manager);

    exec.spin();
    exec.remove_node(action_server->node());
    exec.remove_node(waypoint_action_server);
    exec.remove_node(distance_trick_action_server);
    exec.remove_node(duration_trick_action_server);
    exec.remove_node(idle_action_server);
    exec.remove_node(obj_rel_waypoint_action_server);
    exec.remove_node(seek_object_action_server);
    exec.remove_node(mission_manager);
    rclcpp::shutdown();
    return 0;
}
#endif