#include "simple_bms.hpp"

using namespace std::chrono_literals;

SimpleBMS::SimpleBMS() : Node("simple_bms") {
    if (init_i2c()){
        // Timer to check voltage & current values at a frequency of 100 hz
        battery_timer = this->create_wall_timer(10ms, std::bind(&SimpleBMS::bms_callback, this));
    }
    // Publisher to Battery topic
    bms_publisher = this->create_publisher<custom_interfaces::msg::Battery>("bms", 10);
}

SimpleBMS::~SimpleBMS() {
    if (i2c_fd >= 0) {
        close(i2c_fd);
    }
}

bool SimpleBMS::init_i2c() {
    if ((i2c_fd = open(I2C_FD, O_RDWR))< 0) {
        std::cout << "error: device not found" << std::endl;
        return false;
    }
    if (ioctl(i2c_fd, I2C_SLAVE, BMS_ADDRESS) < 0) {
        std::cout << "error: Failed to connect" << std::endl;
        return false;
    }
    // config sensor
    uint8_t config[3];
    config[0] = 0x01;
    config[1] = 0x42;
    config[2] = 0x83;
    if (write(i2c_fd, config, 3) != 3) {
        std::cout << "error: could not write to config" << std::endl;
        return false;
    }
    // wait for conversion
    usleep(10000);
    // read from conversion register
    uint8_t conv_reg[1] = {0x00};
    if (write(i2c_fd, conv_reg, 1) != 1) {
        std::cerr << "Failed to set pointer to conversion register." << std::endl;
        return false;
    }
    return true;
}

// contains all function calls that should be performed 
void SimpleBMS::bms_callback() {
    // read from channels
    SimpleBMS::BatteryStatus status = readBMS();
    // publish to topic
    publish_bms(status);
}

SimpleBMS::BatteryStatus SimpleBMS::readBMS() {
    // get reading from sensor
    SimpleBMS::BatteryStatus status = {0.0f,0.0f};
    uint8_t output[2];
    if (read(i2c_fd, output, 2) != 2) {
        std::cout << "error: could not read from conversion register" << std::endl;
        return status;
    }
    // reconstruct voltage from output
    int16_t voltage = (output[0] << 8) | output[1];
    status.voltage = voltage * 0.000125f;
    // TODO get current
    return status;
}

void SimpleBMS::publish_bms(SimpleBMS::BatteryStatus status) {
    auto bms = custom_interfaces::msg::Battery();
    bms.voltage = status.voltage;
    bms.current = status.current;
    this->bms_publisher->publish(std::make_unique<custom_interfaces::msg::Battery>(bms));
}

#ifndef ENABLE_TESTING
int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SimpleBMS>());
    rclcpp::shutdown();
    return 0;
}
#endif