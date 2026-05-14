#include "mission_manager_node.hpp"
using namespace std::chrono_literals;

MissionManagerNode::MissionManagerNode() : rclcpp::Node("mission_manager") {
  prime_service =  this->create_service<std_srvs::srv::Trigger>("prime_signal_service", std::bind(&MissionManagerNode::trigger_prime_signal, this, std::placeholders::_1, std::placeholders::_2));
  go_client = this->create_client<std_srvs::srv::Trigger>("go_signal_service");
  execute_tree_client = rclcpp_action::create_client<ExecuteTree>(this, "mission_manager_node");
  heartbeat_timer = this->create_wall_timer(500ms, std::bind(&MissionManagerNode::heartbeat_callback, this));

  mission_manager_heartbeat_publisher = this->create_publisher<std_msgs::msg::Empty>("mission_manager_heartbeat", 10);
}

/*
    get trigger from website (prime signal)
*/
void MissionManagerNode::trigger_prime_signal(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
    (void) request;
    prime_signal = true;
    response->success = true;
    if (!go_signal_requested) {
        go_signal_subscriber = this->create_subscription<std_msgs::msg::Bool>("go_signal", 10, std::bind(&MissionManagerNode::go_signal_callback, this, std::placeholders::_1));
        retrieve_go_signal();
        go_signal_requested = true;
    }
}

/*  asks for the current go switch state from the go_signal_service
    only done once at startup of the node
*/
void MissionManagerNode::retrieve_go_signal() {
    // if service is down, try again in 2 sec
    if (!go_client->wait_for_service(std::chrono::seconds(1))) {
        RCLCPP_WARN(this->get_logger(), "Go signal service not available, retrying in 2 seconds");
        if (!go_retry_timer) {
            go_retry_timer = this->create_wall_timer(std::chrono::seconds(2), std::bind(&MissionManagerNode::retrieve_go_signal, this));
        }
        return;
    }
    if (go_retry_timer) {
        go_retry_timer->cancel();
        go_retry_timer->reset();
    }
    auto go_signal_request = std::make_shared<std_srvs::srv::Trigger::Request>();
    auto future = go_client->async_send_request(go_signal_request);
    auto result = rclcpp::spin_until_future_complete(this->get_node_base_interface(), future);
    if (result != rclcpp::FutureReturnCode::SUCCESS) {
        RCLCPP_WARN(this->get_logger(), "Can't call go signal service");
        return;
    }
    auto response = future.get();
    if (!response->success) {
        RCLCPP_WARN(this->get_logger(), "Go signal trigger failed: %s", response->message.c_str());
        return;
    }
    try_start_mission();
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
   if (!prime_signal || !go_signal || mission_started) {
        return;
   }
   ExecuteTree::Goal goal;
   goal.target_tree = "Mission File";
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

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
   
    rclcpp::NodeOptions options;
    auto action_server = std::make_shared<MissionTreeServer>(options);
    auto mission_manager = std::make_shared<MissionManagerNode>();
    // TODO: This workaround is for a bug in MultiThreadedExecutor where it can deadlock when spinning without a timeout.
    // Deadlock is caused when Publishers or Subscribers are dynamically removed as the node is spinning.
    rclcpp::executors::MultiThreadedExecutor exec(rclcpp::ExecutorOptions(), 0, false,
                                                std::chrono::milliseconds(250));
    exec.add_node(action_server->node());
    exec.add_node(mission_manager);

    exec.spin();
    exec.remove_node(action_server->node());
    exec.remove_node(mission_manager);
    rclcpp::shutdown();
    return 0;
}
