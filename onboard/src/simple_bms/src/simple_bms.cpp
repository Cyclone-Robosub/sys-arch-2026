#include "simple_bms.hpp"

using namespace std::chrono_literals;

SimpleBMS::SimpleBMS() : Node("simple_bms") {
    if (init_i2c()){
        // Timer to check voltage & current values at a frequency of 100 hz
        // FIXME set this to 60ms temporarily to make sure I am not running into issues, this should be changed down once I understand what is happening better
        battery_timer = this->create_wall_timer(60ms, std::bind(&SimpleBMS::bms_callback, this)); // This has been changed to 20ms from 10ms since it needs to wait 10ms in between reading the voltage and the current
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
    // Open and connect to the ADC
    if ((i2c_fd = open(I2C_FD, O_RDWR))< 0) {
        std::cout << "error: device not found" << std::endl;
        return false;
    }
    if (ioctl(i2c_fd, I2C_SLAVE, BMS_ADDRESS) < 0) {
        std::cout << "error: Failed to connect" << std::endl;
        return false;
    }
    
    return config_i2c(VOLTAGE_CONFIG);
    
}

bool SimpleBMS::config_i2c(SimpleBMS::ConfigValues conf){
    uint8_t config[3];
    config[0] = conf.conf_reg;
    config[1] = conf.lsb;
    config[2] = conf.msb;

    if (write(i2c_fd, config, 3) != 3) {
        std::cout << "error: could not write to config" << std::endl;
        return false;
    }

    // wait for conversion
    usleep(10000); //10ms in microseconds

    // read from conversion register
    uint8_t conv_reg[1] = {conf.conv_reg_val};
    if (write(i2c_fd, conv_reg, 1) != 1) {
        std::cerr << "Failed to set pointer to conversion register." << std::endl;
        return false;
    }
    return true;
}

// contains all function calls that should be performed 
void SimpleBMS::bms_callback() {
    // FIXME add a variable here for safety to make sure it is on the correct i2c configuration

    SimpleBMS::BatteryStatus status = {0.0f,0.0f};

    // read voltage. i2c is configured to read voltage upon init and at the end of the bms_callback here 
    status.voltage = readBMS(true);

    // configure and read current
    if (!config_i2c(CURRENT_CONFIG)) return; // No need for an error message here; that is handled in config_current
    status.current = readBMS(false);

    // publish to topic before resetting back to the configuration for voltage, just in case the configuration fails
    publish_bms(status);

    // Configure for reading voltage on the next callback
    if (!config_i2c(VOLTAGE_CONFIG)) return;
}

float SimpleBMS::readBMS(bool isVoltage) {
    // get reading from sensor. This will either be Voltage on pin A0 or current on pin A1, depending on how it was configured before this function was called

    uint8_t output[2];
    if (read(i2c_fd, output, 2) != 2) {
        std::cout << "error: could not read from conversion register" << std::endl;
        return 0.0f;
    }
    // reconstruct value from output, using the relevant scalar depending on whether it is reading current or voltage
    int16_t combined_out = (output[0] << 8) | output[1];
    return combined_out * ((isVoltage) ? 0.000125f : 1.0f);
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