#ifndef THRUST_INTERFACE_HPP
#define THRUST_INTERFACE_HPP

#include <rclcpp/rclcpp.hpp>
#include <custom_interfaces/msg/pwms.hpp>
#include "std_msgs/msg/bool.hpp"
#include <mutex>
#include <vector>
#include <string>
#include <chrono>

using namespace rclcpp;

class FD_Interface {
protected:
    int fd;
public:
    explicit FD_Interface() {};
    virtual int get_fd() = 0;
    virtual void attempt_reconnect() = 0;
    virtual void close_fd() = 0;
};

class Path_FD : public FD_Interface {
protected:
    std::string path;
    int open_pico_serial();
public:
    Path_FD(std::string path);
    int get_fd() override;
    void attempt_reconnect() override;
    void close_fd() override;
    ~Path_FD();
};

class Direct_FD : public FD_Interface {
public:
    Direct_FD(int fd);
    int get_fd() override;
    void attempt_reconnect() override;
    void close_fd() override;
    ~Direct_FD();
};

class Thrust_Interface : public rclcpp::Node {
public:
    Thrust_Interface(std::vector<int> thrusters, 
                    std::unique_ptr<FD_Interface> pico_fd, 
                    int min_pwm, int max_pwm);

private:
    void pwm_received_subscription_callback(custom_interfaces::msg::Pwms::UniquePtr pwms_msg);
    void send_pwm_to_pico(int thruster, int pwm);
    
    void mux_heartbeat_received_callback(std_msgs::msg::Bool::UniquePtr heartbeat);
    void evaluate_mux_heartbeat_freshness();
    void send_heartbeat_to_pico();
    void heartbeat_callback();
    rclcpp::Subscription<custom_interfaces::msg::Pwms>::SharedPtr pwm_received_subscription;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr heartbeat_subscription;
    rclcpp::TimerBase::SharedPtr heartbeat_timer;
    std::vector<int> thrusters;
    std::unique_ptr<FD_Interface> pico_fd;
    int min_pwm;
    int max_pwm;
    std::chrono::time_point<std::chrono::steady_clock> most_recent_heartbeat;
    bool no_heartbeat;

    std::mutex serial_mutex;
};

#endif // THRUST_INTERFACE_HPP