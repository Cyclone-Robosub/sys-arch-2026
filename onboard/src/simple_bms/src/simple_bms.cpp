#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include "simple_bms.hpp"

SimpleBMS::SimpleBMS() {
    // Timer to check voltage & current values at a frequency of 100 hz
    battery_timer = this->create_wall_timer(10ms, std::bind(&SoftMux::bms_callback, this));
    // Publisher to Battery topic
    bms_publisher = this->create_publisher<custom_interfaces::msg::Battery>("bms", 10);
}

// contains all function calls that should be performed 
void SimpleBMS::bms_callback() {
    // read from channels
    BatteryStatus status = readBMS()
    // convert values
    status.voltage = status.voltage * 0.000125f;
    std::cout << "voltage: " << status.voltage << std::endl;
    // publish to topic
    publish_bms(status);
}

BatteryStatus SimpleBMS::readBMS(const std::string& I2C_FD) {
    // get reading from sensor
    BatteryStatus status = {0,0}; // get values 
    int file;
    if ((file = open(I2C_FD, O_RDWR))< 0) {
        std::cout << "error: device not found" << std::endl;
    }
    if (ioctl(file, I2C_SLAVE, BMS_ADDRESS) < 0) {
        std::cout << "error: Failed to connect" << std::endl;
    }
    // config sensor
    uint8_t config[3];
    config[0] = 0x01;
    config[1] = 0xC3;
    config[2] = 0x83;
    if (write(file, config, 3) != 3) {
        std::cout << "error: could not write to config" << std::endl;
    }
    // wait for conversion
    usleep(10000);
    // read from conversion register
    uint8_t conv_reg[1] = {0x00};
    uint8_t output[2];
    if (read(file, output, 2) != 2) {
        std::cout << "error: could not read from conversion register" << std::endl;
    }
    // reconstruct voltage from output
    status.voltage = (output[0] << 8) | output[1];
    // todo get current
    return status;
}

void SimpleBMS::publish_bms(BatteryStatus status) {
    auto bms = custom_interfaces::msg::Battery();
    bms.voltage = status.voltage;
    bms.current = status.current
    this->bms_publisher->publish(std::make_unique<custom_interfaces::msg::Battery>(bms))
}