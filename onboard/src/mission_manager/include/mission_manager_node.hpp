#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include "std_srvs/srv/trigger.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/empty.hpp"
#include <behaviortree_ros2/tree_execution_server.hpp>
#include "server/mission_tree_server.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "btcpp_ros2_interfaces/action/execute_tree.hpp"

class MissionManagerNode : public rclcpp::Node {
    using ExecuteTree = btcpp_ros2_interfaces::action::ExecuteTree;

    public:
        friend class MissionManagerNodeInterface_TestReadySignal_Test;
        friend class MissionManagerNodeInterface_TestGoSignal_Test;
        friend class MissionManagerNodeInterface_TestMissionStart_Test;
        MissionManagerNode();
        void trigger_ready_signal(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response);
        void go_signal_callback(std_msgs::msg::Bool::SharedPtr signal);
        void try_start_mission();
    private:
        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr ready_service;
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr go_signal_subscriber;
        rclcpp_action::Client<ExecuteTree>::SharedPtr execute_tree_client;

        bool ready_signal = false;
        bool go_signal = false;
        bool mission_started = false;
        
        void heartbeat_callback();
        void mission_manager_heartbeat_send();
        rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr mission_manager_heartbeat_publisher;
        rclcpp::TimerBase::SharedPtr heartbeat_timer;
};
