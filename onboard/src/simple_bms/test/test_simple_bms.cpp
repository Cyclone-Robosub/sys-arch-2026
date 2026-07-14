#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>

#include "simple_bms.hpp"

#include <chrono>


/**
* @brief Test code for Simple_BMS node
* This code will create a mock serial device to test the
* simple bms without requiring actual hardware.
*/

class TestSimpleBMS : public ::testing::Test {
protected:
    std::shared_ptr<SimpleBMS> node;
};
