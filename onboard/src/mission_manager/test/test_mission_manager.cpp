#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "mission_manager_node.hpp"

using namespace std::chrono_literals;

class MissionManagerNodeInterface : public::testing::Test {
    protected:
        std::shared_ptr<MissionManagerNode> node;
        rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr go_signal_publisher;

        void SetUp() override {
            // Initialize ROS2
            if (!rclcpp::ok()) {
                rclcpp::init(0, nullptr);
            }
        }
        void TearDown() override {
            node.reset();
            rclcpp::shutdown();
        }
        void createMissionManagerNode() {
            node = std::make_shared<MissionManagerNode>();
        }
        void setUpGoPublisher() {
            go_signal_publisher = node->create_publisher<std_msgs::msg::Bool>("go_signal", 10);
        }
        /*
        *   
        */
        
};

TEST_F(MissionManagerNodeInterface, MissionManagerNodeConstruction) {
    ASSERT_NO_THROW({
        createMissionManagerNode();
    });
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->get_name(), std::string("mission_manager"));
}
TEST_F(MissionManagerNodeInterface, TestReadySignal) {
    createMissionManagerNode();
    auto client = node->create_client<std_srvs::srv::Trigger>("prime_signal_service");
    
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);

    std::thread spin_thread([&executor]() {
        executor.spin();
    });

    std::shared_ptr<std_srvs::srv::Trigger::Request> request = std::make_shared<std_srvs::srv::Trigger::Request>();
    auto future = client->async_send_request(request);

    ASSERT_EQ (future.wait_for(std::chrono::seconds(1)), std::future_status::ready);
    EXPECT_EQ(node->ready_signal, true);
}
TEST_F(MissionManagerNodeInterface, TestGoSignal) {
    createMissionManagerNode();
    std_msgs::msg::Bool msg;
    msg.data = false;
    go_signal_publisher->publish(msg);
    EXPECT_EQ(node->go_signal, false);
    msg.data = true;
    go_signal_publisher->publish(msg);
    EXPECT_EQ(node->go_signal, true);
}
TEST_F(MissionManagerNodeInterface, TestMissionStart) {
    node->ready_signal = true;
    node->go_signal = true;
    EXPECT_EQ(node->mission_started, true);
}
#ifdef ENABLE_TESTING
    int main(int argc, char** argv) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
#endif