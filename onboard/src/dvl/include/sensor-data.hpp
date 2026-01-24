#pragma once

#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <cstring>
#include <iostream>
#include "custom_interfaces/msg/config.hpp"
#include "custom_interfaces/msg/vr.hpp"
#include "custom_interfaces/msg/drr.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_srvs/srv/set_bool.hpp"

namespace dvl {
struct VR {
    float vx = 0, vy = 0, vz = 0, altitude = 0, fom = 0, time = 0;
    std::array<float,9> covariance = {0};
    int64_t time_of_validity = 0, time_of_transmission = 0;
    char valid = 'n';
    uint8_t status = 0x00; 
};

struct DRR {
    int64_t time_stamp = 0;
    float x = 0, y = 0, z = 0, pos_std = 0, roll = 0, pitch = 0, yaw = 0;
    uint8_t status = 0x00;
};

struct Config {
    float speed_of_sound;
    float mounting_rotation_offset;
    std::string acoustic_enabled; //y or n
    std::string dark_mode_enabled; //y or n
    std::string range_mode = "auto";
    std::string periodic_cycling_enabled; //y or n
};

// Protocol definitions
static constexpr uint8_t SOP = 'w'; //start of package
static constexpr std::array<uint8_t,2> EOP = {'\n','\r'}; //possible end of packets bytes
static constexpr uint8_t DIR_CMD = 'c'; //command
static constexpr uint8_t DIR_RESP = 'r'; //response
static constexpr uint8_t CS = '*'; //checksum 

//valid options for [CMD] in outgoing message
static constexpr uint8_t CMD_GET_VERSION = 'v';
static constexpr uint8_t CMD_GET_PRODUCT_DETAIL = 'w';
static constexpr uint8_t CMD_SET_SETTINGS = 's';
static constexpr uint8_t CMD_GET_SETTINGS = 'c';
static constexpr uint8_t CMD_RESET_DR = 'r';
static constexpr uint8_t CMD_TRIGGER_PING = 'x';
static constexpr uint8_t CMD_CALIBRATE_GYRO = 'g';
static constexpr uint8_t CMD_CHANGE_SER_OUTPUT = 'p';

static constexpr uint8_t REC_VR = 'z'; //receive velocity report
static constexpr uint8_t REC_TR = 'u'; //receive transducer report
static constexpr uint8_t REC_DRR = 'p'; //receive dead reckoning report

static constexpr uint8_t ACK = 'a';

// list of valid outgoing commands
static constexpr std::array<char,8> VALID_OUT = {CMD_GET_VERSION, CMD_GET_PRODUCT_DETAIL, CMD_SET_SETTINGS, CMD_GET_SETTINGS, CMD_RESET_DR, CMD_TRIGGER_PING, CMD_CALIBRATE_GYRO, CMD_CHANGE_SER_OUTPUT};

// list of valid received commands
static constexpr std::array<char,11> VALID_IN = {REC_VR, REC_TR, REC_DRR, CMD_GET_VERSION, CMD_GET_PRODUCT_DETAIL, CMD_SET_SETTINGS, CMD_GET_SETTINGS, CMD_RESET_DR, CMD_TRIGGER_PING, CMD_CALIBRATE_GYRO, CMD_CHANGE_SER_OUTPUT};

uint8_t crc8(uint8_t*, int);

class DVL : public rclcpp::Node {
    public:

        DVL(const std::string& port, unsigned long baudrate = 115200) : rclcpp::Node ;

        
        // PUBLIC API //
        //reads from actual DVL
        VR readVelocityReport(); //velocity report
        DRR readDRReport(); //dead reckoning report
        std::string readVersion();
        std::string readDetails();
        Config readConfig();

        //sets (returns true if acknowledge was received)
        bool setConfig(float, float, std::string, std::string, std::string, std::string);
        bool resetDRR(); //reset the dead reckoning report
        bool resetGyro(); //zero the gyroscope
        bool setSerialProtocol(int);
        bool triggerPing();
    private:
        rclcpp::Publisher<custom_interfaces::msg::VR>::SharedPtr velocity_report_publisher;
        rclcpp::Publisher<custom_interfaces::msg::DRR>::SharedPtr drr_report_publisher;
        rclcpp::Publisher<custom_interfaces::msg::Config>::SharedPtr config_publisher;

        rclcpp::Service<custom_interfaces::msg::Config>::SharedPtr setConfig;
        rclcpp::Service<custom_interfaces::msg::DRR>::SharedPtr resetDRR;
        rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr resetGyro;
        rclcpp::Service<std_msgs::msg::Int32>::SharedPtr setSerProtocol;

        /*
        Outgoing messages are expected in the format "[SOP][DIR_CMD][CMD],[option 1],[option 2],...,[option n],[CS],[CHECKSUM]\n". Options are only needed for some commands

        Incoming messages are expected in the format "[SOP]{DIR_RESP][CMD],[option 1],[option 2],...,[option n],[CS],[CHECKSUM]\n" Options are only needed for some commands. EOP may be "\n", "\r", or "\r\n"
        */

        // PRIVATE VARS //
        int fd;
        VR vr, error_vr;
        DRR drr, error_drr;

        Config config, error_config;
        
        std::string version; //Protocol version "major.minor.patch"
        std::string product_details;

        // PRIVATE METHODS //
        bool parseResponse(std::string&); //parses text string from DVL into the results structure
        bool holdForResponse(const char); 
        bool sendCommand(uint8_t, const std::vector<std::string>& = {});
};

}
