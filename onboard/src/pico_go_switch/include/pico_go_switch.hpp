#ifndef PICO_GO_SWITCH_HPP
#define PICO_GO_SWITCH_HPP

#include <rclcpp/rclcpp.hpp>
#include <custom_interfaces/msg/pwms.hpp>
#include "std_msgs/msg/bool.hpp"
#include "fd_interface.hpp"
#include <vector>
#include <string>
#include <chrono>

using namespace rclcpp;

class Pico_FD : public Path_FD {
protected:
    int open_file() override;
public:
    Pico_FD(std::string path);
};


class Pico_Go_Switch : public rclcpp::Node {
public:
    Pico_Go_Switch(std::unique_ptr<FD_Interface> pico_fd);

private:    
    void check_for_go_signal();
    void publish_go_signal();

    rclcpp::TimerBase::SharedPtr go_signal_check_timer;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr heartbeat_publisher;
    std::unique_ptr<FD_Interface> pico_fd;
};

#endif // PICO_GO_SWITCH_HPP
