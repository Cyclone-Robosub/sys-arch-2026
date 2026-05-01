#include <behaviortree_ros2/tree_execution_server.hpp>
#include "custom_logger.hpp"

using namespace BT;

struct mission_file_report {
    std::string subtree;
    std::string command;
    std::string status;
};

class MissionTreeServer : public TreeExecutionServer {
    public:
        explicit MissionTreeServer(const rclcpp::NodeOptions& options);
    private:
        mission_file_report current_mission;
        bool progress_dirty_;
        std::shared_ptr<CustomLogger> logger_cout_;
};