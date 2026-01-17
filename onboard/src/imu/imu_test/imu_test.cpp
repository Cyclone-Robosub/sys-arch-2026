#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32_multi_array.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"


#include "rclcpp/rclcpp.hpp"
#include <gtest/gtest.h>

std::shared_ptr<custom_interfaces::msg::Imu> latest_imu_data = nullptr;
std::atomic<int> count = 0;
void IMU_CUSTOM_callback(const custom_interfaces::msg::Imu::SharedPtr msg) {
    latest_imu_data = msg;
    count++;
}
 auto node = rclcpp::Node::make_shared("imu_topic_node");
TEST(imu_package, ImuCustomMessageTopicDataValidation) {
    auto sub = node->create_subscription<custom_interfaces::msg::Imu>(
        "imu_topic", 10, &IMU_CUSTOM_callback);
    bool isChanged = false;
    count = 0;
    loopcount = 0;
    while(count < 15){
        std::cout << "Current Count: " << count << std::endl;
        loopcount++;
        std::this_thread::sleep(); //(15-count)/100 seconds later  
    }
    EXPECT_LT(loopcount, 2);
    
    //Show Examples of the custom message
}
//Think about benchamrking each topic and then combining topics with the sleep timer.
int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}