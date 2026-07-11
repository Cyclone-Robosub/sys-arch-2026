#include "mission_manager_node.hpp"
using namespace std::chrono_literals;

MissionManagerNode::MissionManagerNode() : rclcpp::Node("mission_manager") {
  this->declare_parameter<std::string>("mission_file", "TrialParamTree");
  param_subscriber = std::make_shared<rclcpp::ParameterEventHandler>(this);
  cb_handle = param_subscriber->add_parameter_callback("mission_file", std::bind(&MissionManagerNode::parameter_callback, this, std::placeholders::_1));
 
  cur_mission = this->get_parameter("mission_file").as_string();
  bt_param_client = std::make_shared<rclcpp::AsyncParametersClient>(this, "/bt_action_server");

  ready_service =  this->create_service<std_srvs::srv::Trigger>("ready_signal_service", std::bind(&MissionManagerNode::trigger_ready_signal, this, std::placeholders::_1, std::placeholders::_2));
  ready_pub_service =  this->create_service<std_srvs::srv::Trigger>("pub_ready_status", std::bind(&MissionManagerNode::pub_ready_status, this, std::placeholders::_1, std::placeholders::_2));
  execute_tree_client = rclcpp_action::create_client<ExecuteTree>(this, "bt_action_server");
  go_signal_subscriber = this->create_subscription<std_msgs::msg::Bool>("go_signal", 10, std::bind(&MissionManagerNode::go_signal_callback, this, std::placeholders::_1));
  heartbeat_timer = this->create_wall_timer(500ms, std::bind(&MissionManagerNode::heartbeat_callback, this));
  mission_manager_heartbeat_publisher = this->create_publisher<std_msgs::msg::Empty>("mission_manager_heartbeat", 10);
  current_ready_status_publisher = this->create_publisher<std_msgs::msg::Bool>("current_ready_state", 10);
  current_mission_status_publisher = this->create_publisher<std_msgs::msg::Bool>("mission_status", 10);

  mission_cmd_service = this->create_service<custom_interfaces::srv::SetMissionCmd>("set_mission_cmd_service", std::bind(&MissionManagerNode::update_mission_cmd_param, this, std::placeholders::_1, std::placeholders::_2));
  get_mission_cmd_service = this->create_service<custom_interfaces::srv::GetMissionCmd>("get_mission_cmd_service", std::bind(&MissionManagerNode::get_mission_cmd_param, this, std::placeholders::_1, std::placeholders::_2));
}


/*
    get trigger from website (ready signal)
*/
void MissionManagerNode::trigger_ready_signal(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
    (void) request;
    publish_mission_status();
    ready_signal = !ready_signal;
    publish_current_ready_status();
    response->success = true;
}

/*
    Publish whether we are currently ready or not. Useful for dashboard monitoring.
*/

void MissionManagerNode::pub_ready_status(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
    (void)request;
    publish_current_ready_status();
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
   mission_started = true;
   publish_mission_status();
   if (idle_goal_handle_) {
        execute_tree_client->async_cancel_goal(idle_goal_handle_);
        idle_goal_handle_.reset();
        return;
   }
   std::this_thread::sleep_for(std::chrono::seconds(15));
   ExecuteTree::Goal goal;
   goal.target_tree = cur_mission;
   goal.payload = buildMissionPayload();
   auto send_goal_options = rclcpp_action::Client<ExecuteTree>::SendGoalOptions();
   send_goal_options.goal_response_callback = std::bind(&MissionManagerNode::goal_response_callback, this, std::placeholders::_1);
   send_goal_options.result_callback = std::bind(&MissionManagerNode::result_callback, this, std::placeholders::_1);
   execute_tree_client->async_send_goal(goal, send_goal_options);
}

void MissionManagerNode::reset_mission() {
    go_signal = false;
    mission_started = false;
    publish_mission_status();

    ExecuteTree::Goal goal;
    goal.target_tree = "IdleAction";
    auto send_goal_options = rclcpp_action::Client<ExecuteTree>::SendGoalOptions();
    send_goal_options.goal_response_callback = std::bind(&MissionManagerNode::idle_goal_response_callback, this, std::placeholders::_1);
    send_goal_options.result_callback = std::bind(&MissionManagerNode::idle_result_callback, this, std::placeholders::_1);
    execute_tree_client->async_send_goal(goal, send_goal_options);
    publish_current_ready_status();
}

void MissionManagerNode::goal_response_callback(GoalHandleExecuteTree::SharedPtr goal_handle) {
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
      reset_mission();
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
    }
}

void MissionManagerNode::idle_goal_response_callback(GoalHandleExecuteTree::SharedPtr goal_handle) {
    if (!goal_handle) {
      idle_goal_handle_.reset();
    } else {
      idle_goal_handle_ = goal_handle;
    }
}


void MissionManagerNode::result_callback(const GoalHandleExecuteTree::WrappedResult & result) {
    switch (result.code) {
        case rclcpp_action::ResultCode::SUCCEEDED:
            break;
        case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
            break;
        case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
            break;
        default:
            RCLCPP_ERROR(this->get_logger(), "Unknown result code");
            break;
    }
    reset_mission();
}

void MissionManagerNode::idle_result_callback(const GoalHandleExecuteTree::WrappedResult & result) {
    ExecuteTree::Goal goal;
    goal.target_tree = cur_mission;
    goal.payload = buildMissionPayload();
    auto send_goal_options = rclcpp_action::Client<ExecuteTree>::SendGoalOptions();
    send_goal_options.goal_response_callback = std::bind(&MissionManagerNode::goal_response_callback, this, std::placeholders::_1);
    send_goal_options.result_callback = std::bind(&MissionManagerNode::result_callback, this, std::placeholders::_1);
    switch (result.code) {
        case rclcpp_action::ResultCode::SUCCEEDED:
            break;
        case rclcpp_action::ResultCode::ABORTED:
            RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
            if (mission_started) {
                execute_tree_client->async_send_goal(goal, send_goal_options);
            }
            break;
        case rclcpp_action::ResultCode::CANCELED:
            RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
            if (mission_started) {
                execute_tree_client->async_send_goal(goal, send_goal_options);
            }
            break;
        default:
            RCLCPP_ERROR(this->get_logger(), "Unknown result code");
            break;
    }
}
void MissionManagerNode::update_mission_cmd_param(const std::shared_ptr<custom_interfaces::srv::SetMissionCmd::Request> request, std::shared_ptr<custom_interfaces::srv::SetMissionCmd::Response> response) {
    std::string key = request->command_id + "." + request->parameter_name;
    mission_params[key] = request->value;
    response->success = true;
}

std::string MissionManagerNode::buildMissionPayload() {
    std::string payload;
    for (const auto& [key, value] : mission_params) {
          payload += key;
          payload += "=";
          payload += value;
          payload += "\n";
    }
    return payload;
}

void MissionManagerNode::get_mission_cmd_param(const std::shared_ptr<custom_interfaces::srv::GetMissionCmd::Request> request, std::shared_ptr<custom_interfaces::srv::GetMissionCmd::Response> response) {
    std::string search_id = request->command_id;
    response->params = "";
    for (const auto& [key, value] : mission_params) {
        size_t pos = key.find(".");
        if (pos != std::string::npos) {
            std::string cmd = key.substr(0, pos);
            if (cmd == search_id) {
                std::string param = key.substr(pos + 1);
                response->params = response->params + "parameter: " + param + ", value: " + value + "\n";
            }
        }
    }
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

void MissionManagerNode::publish_current_ready_status() {
    auto ready = std_msgs::msg::Bool();
    ready.data = ready_signal;
    current_ready_status_publisher->publish(ready);
}

void MissionManagerNode::publish_mission_status() {
    auto mission_status = std_msgs::msg::Bool();
    mission_status.data = mission_started;
    current_mission_status_publisher->publish(mission_status);
}

void MissionManagerNode::parameter_callback(const rclcpp::Parameter & p) {
    RCLCPP_INFO(
        this->get_logger(), "Received an update to parameter \"%s\" of type %s: \"%s\"",
        p.get_name().c_str(),
        p.get_type_name().c_str(),
        p.as_string().c_str());
    cur_mission = this->get_parameter("mission_file").as_string();
    if (bt_param_client->service_is_ready()) {
        bt_param_client->set_parameters({rclcpp::Parameter("mission_file", cur_mission)});
    }
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
    auto dropper_action_server = std::make_shared<DropperActionServer>();
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
    exec.add_node(dropper_action_server);
    exec.add_node(mission_manager);

    exec.spin();
    exec.remove_node(action_server->node());
    exec.remove_node(waypoint_action_server);
    exec.remove_node(distance_trick_action_server);
    exec.remove_node(duration_trick_action_server);
    exec.remove_node(idle_action_server);
    exec.remove_node(obj_rel_waypoint_action_server);
    exec.remove_node(seek_object_action_server);
    exec.remove_node(dropper_action_server);
    exec.remove_node(mission_manager);
    rclcpp::shutdown();
    return 0;
}
#endif
