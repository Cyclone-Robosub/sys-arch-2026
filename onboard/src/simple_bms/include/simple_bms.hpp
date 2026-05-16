#ifndef SIMPLE_BMS_HPP
#define SIMPLE_BMS_HPP

#include <custom_interfaces/msg/battery.hpp>
#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

using namespace rclcpp;

class SimpleBMS : public rclcpp::Node {

    public:
        struct BatteryStatus {
            float voltage;
            float current;
        };

        SimpleBMS();
        ~SimpleBMS();

    private:
        const char* I2C_FD = "/dev/i2c-1";
        const int BMS_ADDRESS = 0x48;
        int i2c_fd = -1;
        
        rclcpp::TimerBase::SharedPtr battery_timer;
        rclcpp::Publisher<custom_interfaces::msg::Battery>::SharedPtr bms_publisher;

        bool init_i2c();
        void bms_callback();
        BatteryStatus readBMS();
        void publish_bms(BatteryStatus status);
};

#endif