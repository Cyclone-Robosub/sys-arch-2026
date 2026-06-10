#ifndef TUI_HPP
#define TUI_HPP

#include <chrono>
#include <unistd.h>
#include <termios.h>
#include <mutex>
#include "rclcpp/rclcpp.hpp"
#include "tui_interface.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "std_srvs/srv/set_bool.hpp"
#include "custom_interfaces/msg/pwms.hpp"
#include "custom_interfaces/msg/vr.hpp"
#include "custom_interfaces/msg/drr.hpp"
#include "custom_interfaces/srv/control_mode.hpp"


using namespace rclcpp;

class Dashboard_TUI : public TUI_Interface {
    public:
        explicit Dashboard_TUI() {};
        virtual void display_tui(va_list args) override;
};

class Dashboard : public rclcpp::Node {
public:
    Dashboard(std::unique_ptr<TUI_Interface> tui);
    void get_mux_mode_now();
    void work_loop();
private:
    // Heartbeats
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr thrust_interface_heartbeat_subscription;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr mux_heartbeat_subscription;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr ctrl_heartbeat_subscription;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr cli_heartbeat_subscription;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr echo_heartbeat_subscription;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr dvl_heartbeat_subscription;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr joystick_heartbeat_subscription;
    
    // Data
    rclcpp::Subscription<custom_interfaces::msg::Pwms>::SharedPtr pwm_cmd_subscription;
    rclcpp::Subscription<custom_interfaces::msg::Pwms>::SharedPtr pwm_ctrl_subscription;
    rclcpp::Subscription<custom_interfaces::msg::Pwms>::SharedPtr pwm_cli_subscription;
    rclcpp::Subscription<custom_interfaces::msg::Pwms>::SharedPtr pwm_echo_subscription;
    rclcpp::Subscription<custom_interfaces::msg::DRR>::SharedPtr dvl_drr_subscription;
    rclcpp::Subscription<custom_interfaces::msg::VR>::SharedPtr dvl_vr_subscription;
    rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr current_control_mode_subscription;
    
    std::unique_ptr<TUI_Interface> tui;

    void mux_heartbeat_received_callback(std_msgs::msg::Empty::UniquePtr heartbeat);
    void heartbeat_check_callback();
    void control_mode_callback(std_msgs::msg::UInt8::UniquePtr msg);
    void refresh_display();

    int current_control_mode = 0; // 0 = Disabled, 1 = CLI, 2 = CTRL, 3 = Echo
    bool no_heartbeat = true;

    rclcpp::Client<custom_interfaces::srv::ControlMode>::SharedPtr client;
    rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr force_pub;

    rclcpp::TimerBase::SharedPtr heartbeat_timer;
    std::chrono::time_point<std::chrono::steady_clock> most_recent_heartbeat;

};

#endif