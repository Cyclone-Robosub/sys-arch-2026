#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include "std_srvs/srv/trigger.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/empty.hpp"
#include "tree_execution_server.hpp"
#include "server/mission_tree_server.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "btcpp_ros2_interfaces/action/execute_tree.hpp"
#include "server/distance_trick_server.hpp"
#include "server/duration_trick_server.hpp"
#include "server/idle_server.hpp"
#include "server/object_rel_waypoint_server.hpp"
#include "server/seek_object_server.hpp"
#include "server/waypoint_server.hpp"
#include "server/dropper_server.hpp"
#include "custom_interfaces/srv/set_mission_cmd.hpp"
#include "custom_interfaces/srv/get_mission_cmd.hpp"

class MissionManagerNode : public rclcpp::Node {
    using ExecuteTree = btcpp_ros2_interfaces::action::ExecuteTree;
    using GoalHandleExecuteTree = rclcpp_action::ClientGoalHandle<ExecuteTree>;
    public:
        friend class MissionManagerNodeInterface_TestReadySignal_Test;
        friend class MissionManagerNodeInterface_TestGoSignal_Test;
        friend class MissionManagerNodeInterface_TestMissionStart_Test;
        MissionManagerNode();
        void trigger_ready_signal(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response);
        void pub_ready_status(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response);
        void go_signal_callback(std_msgs::msg::Bool::SharedPtr signal);
        void try_start_mission();
        void reset_mission();
    private:
        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr ready_service;
        rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr ready_pub_service;
        rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr go_signal_subscriber;
        rclcpp_action::Client<ExecuteTree>::SharedPtr execute_tree_client;
        std::string cur_mission;

        bool ready_signal = false;
        bool go_signal = false;
        bool mission_started = false;
        
        void heartbeat_callback();
        void mission_manager_heartbeat_send();
        void publish_current_ready_status();
        void publish_mission_status();
        void parameter_callback(const rclcpp::Parameter & p);
        void goal_response_callback(GoalHandleExecuteTree::SharedPtr goal_handle);
        void result_callback(const GoalHandleExecuteTree::WrappedResult & result);
        void idle_goal_response_callback(GoalHandleExecuteTree::SharedPtr goal_handle);
        void idle_result_callback(const GoalHandleExecuteTree::WrappedResult & result);
        GoalHandleExecuteTree::SharedPtr idle_goal_handle_;

        rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr mission_manager_heartbeat_publisher;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr current_ready_status_publisher;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr current_mission_status_publisher;
        rclcpp::TimerBase::SharedPtr heartbeat_timer;

        std::shared_ptr<DistanceTrickActionServer> distance_trick_action_server;
        std::shared_ptr<DurationTrickActionServer> duration_trick_action_server;
        std::shared_ptr<IdleActionServer> idle_action_server;
        std::shared_ptr<ObjRelWaypointActionServer> obj_rel_waypoint_action_server;
        std::shared_ptr<SeekObjectActionServer> seek_object_action_server;
        std::shared_ptr<WaypointActionServer> waypoint_action_server;
        std::shared_ptr<DropperActionServer> dropper_action_server;

        std::shared_ptr<rclcpp::ParameterEventHandler> param_subscriber;
        std::shared_ptr<rclcpp::ParameterCallbackHandle> cb_handle;
        std::shared_ptr<rclcpp::AsyncParametersClient> bt_param_client;

        rclcpp::Service<custom_interfaces::srv::SetMissionCmd>::SharedPtr mission_cmd_service;
        std::unordered_map<std::string, std::string> mission_params;
        void update_mission_cmd_param(const std::shared_ptr<custom_interfaces::srv::SetMissionCmd::Request> request, std::shared_ptr<custom_interfaces::srv::SetMissionCmd::Response> response);
        std::string buildMissionPayload();
        rclcpp::Service<custom_interfaces::srv::GetMissionCmd>::SharedPtr get_mission_cmd_service;
        void get_mission_cmd_param(const std::shared_ptr<custom_interfaces::srv::GetMissionCmd::Request> request, std::shared_ptr<custom_interfaces::srv::GetMissionCmd::Response> response);
        rclcpp::Service<custom_interfaces::srv::TerminateMission>::SharedPtr terminate_mission_service;
};
