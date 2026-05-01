#include <behaviortree_ros2/tree_execution_server.hpp>
#include "custom_logger.hpp"

using namespace BT;

class MissionTreeServer : public TreeExecutionServer {
    public:
        explicit MissionTreeServer(const rclcpp::NodeOptions& options);
        void onTreeCreated(BT::Tree& tree);
        std::optional<BT::NodeStatus> onLoopAfterTick(BT::NodeStatus status);
        void registerNodesIntoFactory (BT::BehaviorTreeFactory& factory);
    private:
        
        std::shared_ptr<CustomLogger> logger_cout_;
};