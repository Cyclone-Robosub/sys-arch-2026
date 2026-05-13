#include "include/mission_manager_node.hpp"
/*
    Creates MissionTreeServer object and spins
*/

MissionManagerNode::MissionManagerNode() : rclcpp::Node("MissionManager") {
  prime_service =  this->create_service<std_srvs::srv::Trigger>("prime_signal_service", std::bind(&MissionManagerNode::trigger_prime_signal, this, std::placeholders::_1));
  go_client = this->create_client<std_srvs::srv::Trigger>("go_signal_service");
  //go_signal_subscriber = this->create_subscription<std_msgs::msg::Bool>("go_signal", 10, std::bind(&MissionManagerNode::go_signal_callback, this, std::placeholders::_1));

  heartbeat_timer = this->create_wall_timer(500ms, std::bind(&MissionManagerNode::heartbeat_callback, this));

  mission_manager_heartbeat_publisher = this->create_publisher<std_msgs::msg::Empty>("mission_manager_heartbeat", 10);
}

void MissionManagerNode::retrieve_go_signal() {
    auto go_signal_request = std::make_shared<std_srvs::srv::Trigger::Request>();
    auto result = go_client->async_send_request(go_signal_request);
    if (rclcpp::spin_until_future_complete(this, result) == rclcpp::FutureReturnCode::SUCCESS) {
       if (result.success) {
          go_signal_callback();
       }
    } else {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service");
    }
}
void MissionManagerNode::trigger_prime_signal(const std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
    prime_signal = true;
    response->success = true;
}

void MissionManagerNode::go_signal_callback(std_msgs::msg::Bool signal) {
     go_signal = signal.data;
}

void MissionManagerNode::heartbeat_callback() {
    mission_manager_heartbeat_send();
}

void MissionManagerNode::mission_manager_heartbeat_send() {
    std_msgs::msg::Empty msg;
    this->mission_manager_heartbeat_publisher->publish(msg);
}

void MissionManagerNode::try_start_mission() {
  if (prime_signal & go_signal) {
    
  }
}

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
