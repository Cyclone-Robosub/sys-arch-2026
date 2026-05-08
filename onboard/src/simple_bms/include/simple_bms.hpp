#ifndef SIMPLE_BMS_HPP
#define SIMPLE_BMS_HPP

#include <rclcpp/rclcpp.hpp>
#include <chrono>

using namespace rclcpp;

class SimpleBMS{

    public:
        struct BatteryStatus = {
            float voltage;
            float current;
        };

        SimpleBMS();
        BatteryStatus readBMS(const std::string& I2C_FD = "/dev/i2c-1");

    private:
        const std::string I2C_FD = "/dev/i2c-1";
        const int BMS_ADDRESS = 0x48;
        
        rclcpp::TimerBase::SharedPtr battery_timer;
        rclcpp::Publisher<custom_interfaces::msg::Battery>::SharedPtr bms_publisher;

        void bms_callback(); // might put this in public, not sure where it belongs
        void publish_bms();
};

#define SIMPLE_BMS_HPP