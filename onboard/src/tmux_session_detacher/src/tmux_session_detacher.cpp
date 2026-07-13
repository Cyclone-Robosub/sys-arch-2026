#include "tmux_session_detacher.hpp"

Tmux_Session_Detacher::Tmux_Session_Detacher(std::string session_name) : Node("tmux_session_detacher"),
    session_name(session_name) {
    detach_session_service = this->create_service<std_srvs::srv::Trigger>("detatch_tmux_session", 
            std::bind(&Tmux_Session_Detacher::detach_session, this, std::placeholders::_1, std::placeholders::_2));
}

void Tmux_Session_Detacher::detach_session(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, const std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
    (void)request; // stop compiler complaining
    // TODO
}

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto tmux_session_detacher = std::make_shared<Tmux_Session_Detacher>("manny");
    rclcpp::spin(tmux_session_detacher);
    
    rclcpp::shutdown();
    
    return 0;
}
