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
    // convert valuesP

    // publish to topic
    publish_bms(status);
}

BatteryStatus SimpleBMS::readBMS(const std::string& I2C_FD) {
    // get reading from sensor
    BatteryStatus status = {}; // get values 
    // return
    return status;
}

void SimpleBMS::publish_bms(BatteryStatus status) {
    auto bms = custom_interfaces::msg::Battery();
    bms.voltage = status.voltage;
    bms.current = status.current
    this->bms_publisher->publish(std::make_unique<custom_interfaces::msg::Battery>(bms))
}