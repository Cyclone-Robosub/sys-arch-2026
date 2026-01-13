#include "rclcpp/rclcpp.hpp"
#include "external/dvl-cpp/include/dvl-cpp.h"
#include "std_msgs/msg/bool.hpp"

class SensorData : public rclcpp::Node {
    public:
        DVL dvl_obj;
    private:
        rclcpp::Service<std_msgs::msg::Bool>::SharedPtr setSettings_mode;
        rclcpp::Service<std_msgs::msg::Bool>::SharedPtr resetDR_mode;
        rclcpp::Service<std_msgs::msg::Bool>::SharedPtr calGyro_mode;
        //find datatype for this
        rclcpp::Publisher<...>::SharedPtr sensor_publisher;
} 