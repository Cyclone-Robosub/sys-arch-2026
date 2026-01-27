#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "sensor-data.hpp"
#include "custom_interfaces/msg/config.hpp"
#include "custom_interfaces/msg/vr.hpp"
#include "custom_interfaces/msg/drr.hpp"

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
    //write valid Velocity Report data into the pipe_fds[0] end

    //check if status returns vr

    //write invalid Velocity Report data into the pipe_fds[0] end

    //check if status returns error_vr
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

 