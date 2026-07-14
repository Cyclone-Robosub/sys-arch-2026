#ifndef TMUX_SESSION_DETACHER_HPP
#define TMUX_SESSION_DETACHER_HPP

#include <stdlib.h>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include "std_srvs/srv/trigger.hpp"



class Tmux_Session_Detacher : public rclcpp::Node {
public:
    Tmux_Session_Detacher(std::string session_name);

private:
    void detach_session(const std::shared_ptr<std_srvs::srv::Trigger::Request> request, const std::shared_ptr<std_srvs::srv::Trigger::Response> response);

    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr detach_session_service;

    std::string session_name;
};


#endif // TMUX_SESSION_DETACHER_HPP