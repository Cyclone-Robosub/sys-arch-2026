#include <behaviortree_ros2/tree_execution_server.hpp>
#include "custom_logger.hpp"
#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/command_tree.hpp"
#include "std_msgs/msg/empty.hpp"
#include <behaviortree_cpp/bt_factory.h>
#include <chrono>
#include <string>


using namespace BT;

class MissionTreeServer : public TreeExecutionServer {
    public:
        explicit MissionTreeServer(const rclcpp::NodeOptions& options);
        void onTreeCreated(BT::Tree& tree);
        std::optional<BT::NodeStatus> onLoopAfterTick(BT::NodeStatus status);
        void registerNodesIntoFactory (BT::BehaviorTreeFactory& factory);
        bool onGoalReceived (const std::string& tree_name, const std::string& payload);
    private:
        std::shared_ptr<CustomLogger> logger_cout_;
        rclcpp::Publisher<custom_interfaces::msg::CommandTree>::SharedPtr current_command_publisher;
        std::string cur_mission;
        std::string mission_file_stored;
        bool nodes_registered = false;


};