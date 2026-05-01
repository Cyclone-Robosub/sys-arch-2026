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

        BatteryStatus readBMS(const std::string& I2C_FD = "/dev/i2c-1");

    private:
        const std::string I2C_FD = "/dev/i2c-1";
        const int BMS_ADDRESS = 0x48;
        

};

#define SIMPLE_BMS_HPP