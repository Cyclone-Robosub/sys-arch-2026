#include "simple_bms.hpp"

SimpleBMS::SimpleBMS() {
    // Timer to check voltage & current values at a frequency of 100 hz
    battery_timer = this->create_wall_timer(10ms, std::bind(&SoftMux::bms_callback, this));
}

// contains all function calls that should be performed 
void SimpleBMS::bms_callback() {
    // read from channels
    // convert values
    // publish to topic
}