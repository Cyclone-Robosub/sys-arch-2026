#include "mission_executor_node.hpp"
#include "bt_nodes/navigate_to_waypoint.hpp"
#include "bt_nodes/detect_object.hpp"
#include "bt_nodes/send_manipulator_command.hpp"
#include "bt_nodes/wait_duration.hpp"
#include "bt_nodes/conditions/battery_ok.hpp"
#include "bt_nodes/conditions/at_waypoint.hpp"
#include "bt_nodes/conditions/object_detected.hpp"

#include <chrono>
#include <functional>
#include <sstream>

using namespace std::chrono_literals;

namespace mission_executive {

MissionExecutorNode::MissionExecutorNode()
    : Node("mission_executor")
{
    this->declare_parameter<std::string>("tree_file", "");
}

void MissionExecutorNode::initialize()
{
    registerBTNodes();
    loadTreeFromParam();
    seedBlackboardFromParams();
    setupSubscriptions();

    // Set up Groot2 publisher for visualization
    groot_publisher_ = std::make_unique<BT::Groot2Publisher>(*tree_, 1667);

    // Tick tree at 100Hz
    tick_timer_ = this->create_wall_timer(10ms, std::bind(&MissionExecutorNode::tickTree, this));

    RCLCPP_INFO(this->get_logger(), "Mission executor initialized, ticking tree at 100Hz");
}

void MissionExecutorNode::registerBTNodes()
{
    // NavigateToWaypoint — StatefulActionNode, uses blackboard-injected ROS node
    factory_.registerNodeType<NavigateToWaypoint>("NavigateToWaypoint");

    // SendManipulatorCommand — currently a SyncActionNode publishing to topic
    // TODO: Migrate to RosActionNode once ManipulateObject.action is defined
    factory_.registerNodeType<SendManipulatorCommand>("SendManipulatorCommand");

    // DetectObject — StatefulActionNode, pass ROS node via blackboard
    factory_.registerNodeType<DetectObject>("DetectObject");

    // WaitDuration — StatefulActionNode, no ROS needed
    factory_.registerNodeType<WaitDuration>("WaitDuration");

    // Condition nodes
    factory_.registerNodeType<BatteryOK>("BatteryOK");
    factory_.registerNodeType<AtWaypoint>("AtWaypoint");
    factory_.registerNodeType<ObjectDetected>("ObjectDetected");
}

void MissionExecutorNode::loadTreeFromParam()
{
    tree_file_ = this->get_parameter("tree_file").as_string();
    if (tree_file_.empty()) {
        RCLCPP_ERROR(this->get_logger(), "No tree_file parameter specified");
        throw std::runtime_error("tree_file parameter is required");
    }

    blackboard_ = BT::Blackboard::create();

    // Inject ROS node into blackboard for nodes that need it
    blackboard_->set("ros_node", this->shared_from_this());

    tree_ = std::make_unique<BT::Tree>(factory_.createTreeFromFile(tree_file_, blackboard_));

    RCLCPP_INFO(this->get_logger(), "Loaded behavior tree from: %s", tree_file_.c_str());
}

void MissionExecutorNode::seedBlackboardFromParams()
{
    // Seed waypoint parameters into blackboard
    // Waypoints are declared as ROS parameters and loaded into blackboard keys
    // Example launch file usage:
    //   parameters=[{'waypoint_1.x': 1.0, 'waypoint_1.y': 2.0, ...}]
    //
    // TODO: Define waypoint parameter schema and loading logic once
    // the mission tree structure is finalized. For now, waypoints can be
    // hardcoded in XML tree files during development.

    RCLCPP_INFO(this->get_logger(), "Blackboard seeded with parameters");
}

void MissionExecutorNode::setupSubscriptions()
{
    // Vision detections — write raw detection strings to blackboard
    // TODO: Define proper detection message type (e.g. vision_msgs or custom)
    // For now, expects comma-separated class names: "GATE,BINS,BUOY"
    detections_sub_ = this->create_subscription<std_msgs::msg::String>(
        "detections", 10,
        [this](const std_msgs::msg::String::SharedPtr msg) {
            std::lock_guard<std::mutex> lock(detections_mutex_);
            detected_objects_.clear();

            std::istringstream stream(msg->data);
            std::string token;
            while (std::getline(stream, token, ',')) {
                if (!token.empty()) {
                    detected_objects_.push_back(token);
                }
            }

            blackboard_->set("detected_objects", detected_objects_);
        });

    // Battery state of charge interrupt
    soc_sub_ = this->create_subscription<std_msgs::msg::Bool>(
        "SOCIntTopic", 10,
        [this](const std_msgs::msg::Bool::SharedPtr msg) {
            battery_ok_ = !msg->data;  // msg->data == true means battery LOW
            blackboard_->set("battery_ok", battery_ok_);
        });

    // Current position
    position_sub_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
        "position_topic", 10,
        [this](const std_msgs::msg::Float32MultiArray::SharedPtr msg) {
            if (msg->data.size() >= 6) {
                std::lock_guard<std::mutex> lock(pose_mutex_);
                current_pose_.position.x = msg->data[0];
                current_pose_.position.y = msg->data[1];
                current_pose_.position.z = msg->data[2];
                // Store euler angles in orientation as a simple convention:
                // TODO: Convert euler (roll, pitch, yaw) to quaternion once
                // the nav stack standardizes on geometry_msgs::Pose
                // For now, store raw floats in blackboard for condition nodes
                blackboard_->set("current_pose", current_pose_);
                blackboard_->set("current_roll", static_cast<double>(msg->data[3]));
                blackboard_->set("current_pitch", static_cast<double>(msg->data[4]));
                blackboard_->set("current_yaw", static_cast<double>(msg->data[5]));
            }
        });

    // Initialize blackboard defaults
    blackboard_->set("battery_ok", true);
    blackboard_->set("detected_objects", std::vector<std::string>{});

    RCLCPP_INFO(this->get_logger(), "ROS subscriptions active: detections, SOCIntTopic, position_topic");
}

void MissionExecutorNode::tickTree()
{
    if (!tree_) return;

    auto status = tree_->tickOnce();

    if (status == BT::NodeStatus::SUCCESS) {
        RCLCPP_INFO(this->get_logger(), "Mission completed successfully");
        tick_timer_->cancel();
    } else if (status == BT::NodeStatus::FAILURE) {
        RCLCPP_ERROR(this->get_logger(), "Mission failed");
        tick_timer_->cancel();
    }
    // RUNNING: continue ticking next cycle
}

}  // namespace mission_executive

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<mission_executive::MissionExecutorNode>();
    node->initialize();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
