#ifndef ECHO_HPP
#define ECHO_HPP

#endif // ECHO_HPP

#include "rclcpp/rclcpp.hpp"
#include "custom_interfaces/msg/pwms.hpp"
#include "fd_interface.hpp"

using namespace rclcpp;

enum Use_Mode {None, Read, Write};

class Echo : public Node {
public:
    Echo(std::unique_ptr<FD_Interface> fd);
    void set_mode(Use_Mode mode);
private:
    std::unique_ptr<FD_Interface> log_fd;
    Use_Mode mode;

    Subscription<custom_interfaces::msg::Pwms>::SharedPtr pwm_received_subscription;
    Publisher<custom_interfaces::msg::Pwms>::SharedPtr pwm_cmd_publisher;
    void pwm_received_subscription_callback(custom_interfaces::msg::Pwms::UniquePtr pwms_msg);
    void log_pwms(std::array<int32_t,8> pwms);
    void echo_pwms();
    std::array<int32_t,8> parseLine(char* line);
};