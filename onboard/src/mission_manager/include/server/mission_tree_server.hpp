#include <behaviortree_ros2/tree_execution_server.hpp>
#include "custom_logger.hpp"
#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/command_tree.hpp"
#include "std_msgs/msg/empty.hpp"
#include <chrono>


using namespace BT;

class MissionTreeServer : public TreeExecutionServer {
    public:
        explicit MissionTreeServer(const rclcpp::NodeOptions& options);
        void onTreeCreated(BT::Tree& tree);
        std::optional<BT::NodeStatus> onLoopAfterTick(BT::NodeStatus status);
        void registerNodesIntoFactory (BT::BehaviorTreeFactory& factory);
    private:
        std::shared_ptr<CustomLogger> logger_cout_;
        rclcpp::Publisher<custom_interfaces::msg::CommandTree>::SharedPtr current_command_publisher;

};