#ifndef CPP_PACKAGE_HPP
#define CPP_PACKAGE_HPP

#include <rclcpp/rclcpp.hpp>
#include <custom_interfaces/msg/pwms.hpp>
#include "std_msgs/msg/empty.hpp"
#include <string>
#include <chrono>

using namespace rclcpp;

class CPP_Template : public rclcpp::Node {
public:
    CPP_Template();

private:
    uint8_t count;
};

#endif // CPP_PACKAGE_HPP