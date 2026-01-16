#ifndef MUX_CONTROLLER_HPP
#define MUX_CONTROLLER_HPP

#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_srvs/srv/set_bool.hpp"
#include "custom_interfaces/msg/pwms.hpp"

using namespace rclcpp;

class Mux_Controller : public rclcpp::Node {
public:
    Mux_Controller();
    void set_mux_mode(bool mode);
    void get_mux_mode_now();
    void work_loop();
    static void clear_display();
private:
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr current_control_mode_subscriber;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr heartbeat_subscription;

    void mux_heartbeat_received_callback(std_msgs::msg::Bool::UniquePtr heartbeat);
    void heartbeat_check_callback();
    void control_mode_callback(std_msgs::msg::Bool::UniquePtr msg);
    void refresh_display();

    bool current_control_mode;

    rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr client;
    rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr force_pub;

    rclcpp::TimerBase::SharedPtr heartbeat_timer;
    std::chrono::time_point<std::chrono::steady_clock> most_recent_heartbeat;

    bool no_heartbeat = true;
};

#endif