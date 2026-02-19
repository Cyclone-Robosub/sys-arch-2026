#ifndef MUX_CONTROLLER_HPP
#define MUX_CONTROLLER_HPP

#include <chrono>
#include <unistd.h>
#include <termios.h>
#include <mutex>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "std_srvs/srv/set_bool.hpp"
#include "custom_interfaces/msg/pwms.hpp"
#include "custom_interfaces/srv/control_mode.hpp"

using namespace rclcpp;

class Mux_Controller : public rclcpp::Node {
public:
    Mux_Controller();
    void set_mux_mode(int mode);
    void get_mux_mode_now();
    void work_loop();
    static void clear_display();
private:
    rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr current_control_mode_subscriber;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr heartbeat_subscription;

    void mux_heartbeat_received_callback(std_msgs::msg::Bool::UniquePtr heartbeat);
    void heartbeat_check_callback();
    void control_mode_callback(std_msgs::msg::UInt8::UniquePtr msg);
    void refresh_display();
    void process_input();
    void backspace();
    void delete_or_direction();
    void insert(char c);

    std::mutex display_mutex;

    int current_control_mode = 0; // 0 = Disabled, 1 = CLI, 2 = CTRL, 3 = Echo
    bool no_heartbeat = true;
    std::string current_input;
    int cursor_pos = 0;
    int num_read = 0;

    rclcpp::Client<custom_interfaces::srv::ControlMode>::SharedPtr client;
    rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr force_pub;

    rclcpp::TimerBase::SharedPtr heartbeat_timer;
    std::chrono::time_point<std::chrono::steady_clock> most_recent_heartbeat;

};

#endif