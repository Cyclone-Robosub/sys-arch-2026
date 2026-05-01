#include <behaviortree_ros2/tree_execution_server.hpp>
#include "custom_logger.hpp"

using namespace BT;

class MissionTreeServer : public TreeExecutionServer {
    public:
        explicit MissionTreeServer(const rclcpp::NodeOptions& options);
    private:
        
        std::shared_ptr<CustomLogger> logger_cout_;
};