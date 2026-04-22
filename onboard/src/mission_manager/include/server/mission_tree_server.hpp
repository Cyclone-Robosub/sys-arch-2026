#include <behaviortree_ros2/tree_execution_server.hpp>



using namespace BT;

class MissionTreeServer : public TreeExecutionServer {
    public:

    private:
        std::string current_command;
        std::shared_ptr<CustomLogger> logger_cout_;
}