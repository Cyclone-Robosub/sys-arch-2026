#include <gtest/gtest.h>
#include <rclcpp/rclcpp.hpp>
#include "dvl.hpp"
#include "fd-interface.hpp"
#include <chrono>

static constexpr uint8_t VR_TYPE = 'v';
static constexpr uint8_t DRR_TYPE = 'd';
static constexpr uint8_t CONFIG_TYPE = 'r';

using namespace dvl;

class TestDVLInterface : public::testing::Test {
protected:
    std::shared_ptr<DVL> node;
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
        node.reset();
        close(pipe_fds[0]);
        close(pipe_fds[1]);
    }

    void create_node(){
        // Use pipe_fds[1] (write end) as the file descriptor
        // The node will write to it, and we'll read from pipe_fds[0]
        std::unique_ptr<FD_Interface> pipe_fd = std::make_unique<Direct_FD>(pipe_fds[1]);

        node = std::make_shared<DVL>(std::move(pipe_fd));
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
    * @brief Helper to write a serial message to pipe_fds[1]
    * 
    * @param data_type The data type of the serial message
    */
    void write_serial_message(uint8_t data_type){
        std::string msg;
        get_serial_message(data_type, msg);
        int length = msg.size();
        write(pipe_fds[1], msg.c_str(), length);
    }

    /**
    * @brief Helper to generate serial messages per data type
    * 
    * @param data_type The data type of the serial message
    * @param msg The message
    */
    void get_serial_message(uint8_t data_type, std::string& msg){
        switch(data_type){
        case VR_TYPE:
            msg = 
                "\t\tz,1.000000,2.000000,3.000000," //vx, vy, vz
                ",2.000000,1.000000," //valid, altitude, fom
                "1.000000,2.000000,3.000000,4.000000,5.000000," //covariance
                "1.000000,2.000000,3.000000,4.000000," //covariance
                "1,2,3.000000,0,\n"; //time of validity, time of transmission, time, status
            break;
        case DRR_TYPE:
            msg =
                "\t\tp,1716814976.000000,0.110000,0.280000,0.040000," //x, y, z, pos_std
                "15.400000,-1.100000,-0.300000,3,\n"; //roll, pitch, yaw, status
            break;
        case CONFIG_TYPE:
            msg =
                "\t\tc,1475.000000,0.000000,y" //speed of sound, mounting rotation offset, acoustic enabled
                "n,auto,y,\n"; //dark mode enabled, range mode, periodic cycling enabled
            break;
        default: 
            msg = "error";
        }
    }
};

/**
 * @brief Test node construction
 */
TEST_F(TestDVLInterface, DVLConstruction) {
    ASSERT_NO_THROW({
        create_node();
    });

    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->get_name(), std::string("dvl"));
}

/**
 * @brief Test DVL reading Velocity
 */
 TEST_F(TestDVLInterface, ValidReadVelocityReport){
    create_node();
    velocity_report vr;

    //write valid VR data into  pipe_fds[1] 
    write_serial_message(VR_TYPE);

    //check if vr was read correctly
    vr = node->readVelocityReport();
    EXPECT_EQ(vr.vx, 1.000000);
    EXPECT_EQ(vr.covariance[3], 4.000000);
    EXPECT_EQ(vr.altitude, 2.000000);
    EXPECT_EQ(vr.fom, 1.000000);
    EXPECT_EQ(vr.time, 3.000000);
    EXPECT_EQ(vr.time_of_validity, 1);
    EXPECT_EQ(vr.time_of_transmission, 2);
    EXPECT_EQ(vr.status, 0);
    EXPECT_EQ(vr.valid, 'n'); 
 }

 /**
 * @brief Test DVL reading DRReport
 */
 TEST_F(TestDVLInterface, ValidReadDRReport){
    create_node();
    dead_reck_report drr;

    //write valid DRR data into pipe_fds[1]
    write_serial_message(DRR_TYPE);

    //check if drr was read correctly
    drr = node->readDRReport();
    EXPECT_EQ(drr.time_stamp, 0); //time stamp is never set? ask Kory??
    EXPECT_EQ(drr.x, 1716814976.000000);
    EXPECT_EQ(drr.roll, 15.400000);
    EXPECT_EQ(drr.status, 0.040000);
 }

 /**
 * @brief Test DVL reading Config
 */
 TEST_F(TestDVLInterface, ValidReadConfiguration){
    create_node();
    config_report config;

    //write valid Config data into pipe_fds[1]
    write_serial_message(CONFIG_TYPE);
    
    //check if config was read correctly
    config = node->readConfig();
    EXPECT_EQ(config.speed_of_sound, 1475.000000);
    EXPECT_EQ(config.mounting_rotation_offset, 0.000000);
    EXPECT_EQ(config.acoustic_enabled, "y");
    EXPECT_EQ(config.dark_mode_enabled, "n");
    EXPECT_EQ(config.range_mode, "auto");
    EXPECT_EQ(config.periodic_cycling_enabled, "y");
 }

 /**
 * @brief Test DVL publishing VR
 */
 TEST_F(TestDVLInterface, DVLPublishVR){
    create_node();

    //write valid VR data into pipe_fds[1] 
    write_serial_message(VR_TYPE);

    //check if publisher has published correct data
    node->publishVR();

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

 