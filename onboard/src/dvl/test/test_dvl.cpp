#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "sensor-data.hpp"
#include "custom_interfaces/msg/config.hpp"
#include "custom_interfaces/msg/vr.hpp"
#include "custom_interfaces/msg/drr.hpp"
#include "fd-interface.hpp"
#include <chrono>

class TestDVLInterface : public::testing::Test {
    protected:
        std::share_ptr<DVL> dvl;
        int pipe_fds[2];  // [0] = read end, [1] = write end

        void SetUp() override {
            if (!rclcpp::ok()) {
                rclcpp::init(0, nullptr);
            }

            // Create pipe for mock serial communication
            // pipe_fds[0] = read end, pipe_fds[1] = write end
            if (pipe(pipe_fds) == -1) {
                FAIL() << "Failed to create pipe for mock serial";
            }
        }

        void TearDown() override {
            dvl.reset();
            close(pipe_fds[0]);
            close(pipe_fds[1]);
        }

        void createDVL(){
            // Use pipe_fds[1] (write end) as the file descriptor
            // The node will write to it, and we'll read from pipe_fds[0]
            int fd = DVL::open_serial(path)
            dvl = std::make_shared<DVL>(pipe_fds[1]);
        }

        /**
     * @brief Helper function to read serial output from the node
     * 
     * @param timeout_ms Maximum time to wait for data
     * @return std::string The data read from the serial interface
     */
    std::string read_serial_output(int timeout_ms = 100) {
        char buffer[1024];
        fd_set readfds;
        struct timeval timeout;
        
        FD_ZERO(&readfds);
        FD_SET(pipe_fds[0], &readfds);
        
        timeout.tv_sec = timeout_ms / 1000;
        timeout.tv_usec = (timeout_ms % 1000) * 1000;
        
        int result = select(pipe_fds[0] + 1, &readfds, nullptr, nullptr, &timeout);
        
        if (result > 0) {
            ssize_t bytes_read = read(pipe_fds[0], buffer, sizeof(buffer) - 1);
            if (bytes_read > 0) {
                buffer[bytes_read] = '\0';
                return std::string(buffer);
            }
        }
        
        return "";
    }

    /**
     * @brief Create a node with custom parameters using test mode
     * 
     */
    void create_node() {
        // Use pipe_fds[1] (write end) as the file descriptor
        // The node will write to it, and we'll read from pipe_fds[0]
        node = std::make_shared<DVL>(
            pipe_fds[1],  // Write end of pipe
        );
    }

    /**
     * @brief Helper to publish VR message and process it
     * 
     * @param msg The VR message to publish
     */
    void publish_and_process_vr(custom_interfaces::msg::VR::SharedPtr vrMessage) {
        auto publisher = node->create_publisher<custom_interfaces::msg::VR>("VR", 10);
        
        // Give publisher time to connect
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        publisher->publish(*vrMessage);
        
        // Process the message
        rclcpp::spin_some(node);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    /**
     * @brief Helper to publish DRR message and process it
     * 
     * @param msg The DRR message to publish
     */
    void publish_and_process_drr(custom_interfaces::msg::DRR::SharedPtr drrMessage) {
        auto publisher = node->create_publisher<custom_interfaces::msg::DRR>("DRR", 10);
        
        // Give publisher time to connect
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        publisher->publish(*drrMessage);
        
        // Process the message
        rclcpp::spin_some(node);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    /**
     * @brief Helper to publish Config message and process it
     * 
     * @param msg The Config message to publish
     */
    void publish_and_process_config(custom_interfaces::msg::VR::SharedPtr configMessage) {
        auto publisher = node->create_publisher<custom_interfaces::msg::Config>("Config", 10);
        
        // Give publisher time to connect
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        publisher->publish(*configMessage);
        
        // Process the message
        rclcpp::spin_some(node);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

};

/**
 * @brief Test dvl construction
 */
TEST_F(TestDVLInterface, DVLConstruction) {
    ASSERT_NO_THROW({
        createDVL();
    });

    ASSERT_NE(dvl, nullptr);
    EXPECT_EQ(dvl->getname(), std::string("dvl"));
}

/**
 * @brief Test DVL reading Velocity
 */
 TEST_F(TestDVLInterface, ReadVelocityReport){
    createDVL();
    VR vr, error_vr;

    //check if status returns error_vr w/o any inputs
    EXPECT_EQ(dvl.readVelocityReport(), error_vr);

    //write valid Velocity Report data into the pipe_fds[1] end
    std::string serial_message = 
        "\t\tz,1.000000,2.000000,3.000000," //vx, vy, vz
        "110,2.000000,1.000000," //valid, altitude, fom
        "1.000000,2.000000,3.000000,4.000000,5.000000," //covariance
        "1.000000,2.000000,3.000000,4.000000," //covariance
        "1,2,3.000000,0," //time of validity, time of transmission, time, status
    std::string expected message =
        "VELOCITY REPORT: v = [1.000000, 2.000000, 3.000000]\n"
        "Figure of Merit = 1.000000\n"
        "Altitude = 2.000000\n" 
        "Time = 3.000000\n" 
        "Time of Validity = 1\n"
        "Time of Transmission = 2\n"
        "Valid = 110\n"
        "Status = 0\n"
        "Covariance values:  1.000000 2.000000 3.000000 4.000000 5.000000 1.000000 2.000000 3.000000 4.000000\n";

    int length = serial_message.size();
    write(pipe_fds[1], serial_message.c_str(), length);

    //check if status returns vr
    EXPECT_EQ(dvl.readVelocityReport(), vr);
 }

 /**
 * @brief Test DVL reading DRReport
 */
 TEST_F(TestDVLInterface, ReadDRReport){
    //write valid DRReport data into the pipe_fds[0] end

    //check if status returns drr

    //write invalid DRReport data into the pipe_fds[0] end

    //check if status returns error_drr
 }

 /**
 * @brief Test DVL reading Config
 */
 TEST_F(TestDVLInterface, ReadVelocityReport){
    //write valid Config data into the pipe_fds[0] end

    //check if status returns config

    //write invalid Config Report data into the pipe_fds[0] end

    //check if status returns error config
 }

 /**
 * @brief Test DVL publishing VR
 */
 TEST_F(TestDVLInterface, DVLPublishVR){
    //write valid VR data into the pipe_fds[0] end

    //check if publisher has published correct data
 }

  /**
 * @brief Test DVL publishing DRR
 */
 TEST_F(TestDVLInterface, DVLPublishDRR){
    //write valid DRR data into the pipe_fds[0] end

    //check if publisher has published correct data
 }

  /**
 * @brief Test DVL publishing Config
 */
 TEST_F(TestDVLInterface, DVLPublishConfig){
    //write valid Config data into the pipe_fds[0] end

    //check if publisher has published correct data
 }

 