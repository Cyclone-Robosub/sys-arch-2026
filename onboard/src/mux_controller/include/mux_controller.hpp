#ifndef MUX_CONTROLLER_HPP
#define MUX_CONTROLLER_HPP

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_srvs/srv/set_bool.hpp>
#include <custom_interfaces/msg/pwms.hpp>

using namespace rclcpp;

class Mux_Controller : public rclcpp::Node {
public:
    Mux_Controller();
    void set_mux_mode(bool mode);
private:
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr current_control_mode_subscriber;
    void control_mode_callback(std_msgs::msg::Bool::UniquePtr msg);
    void refresh_display();

    bool current_control_mode;
    rclcpp::Client<std_srvs::srv::SetBool>::SharedPtr client;
};

#endif