#include "data_logger.hpp"

using namespace std::chrono_literals;
using namespace rclcpp;
#include <iostream>

Data_Logger::Data_Logger() : Node("data_logger") {
    drr_subscription = this->create_subscription<custom_interfaces::msg::DRR>(
        "dead_reck_report", 10, 
        std::bind(&Data_Logger::dead_reck_report_received_callback, this, std::placeholders::_1));
    vr_subscription = this->create_subscription<custom_interfaces::msg::VR>(
        "velocity_report", 10, 
        std::bind(&Data_Logger::velocity_report_received_callback, this, std::placeholders::_1));
}

void Data_Logger::dead_reck_report_received_callback(custom_interfaces::msg::DRR::UniquePtr drr_msg) {
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);
    std::puts(buffer);
    
    std::cout << drr_msg->time_stamp;
    std::cout << drr_msg->position.x;
    std::cout << drr_msg->position.y;
    std::cout << drr_msg->position.z;
    std::cout << drr_msg->angle.x;
    std::cout << drr_msg->angle.y;
    std::cout << drr_msg->angle.z;
    std::cout << drr_msg->pos_std;
    std::cout << "\n";
}

void Data_Logger::velocity_report_received_callback(custom_interfaces::msg::VR::UniquePtr vr_msg) {
    std::cout << "VR" << "\n";
    std::cout << vr_msg->velocity_data.x;
    std::cout << vr_msg->velocity_data.y;
    std::cout << vr_msg->velocity_data.z;
    std::cout << vr_msg->altitude; 
    std::cout << vr_msg->fom;
    std::cout << vr_msg->time;
    for (auto cov_data : vr_msg->covariance.data) {
        std::cout << cov_data;
    }
    std::cout << vr_msg->time_of_validity;
    std::cout << vr_msg->time_of_transmission;
    std::cout << vr_msg->status;
    std::cout << "\n";
}

std::string Data_Logger::get_current_time() {
    char buffer [80];

    std::time_t rawtime;
    std::tm* timeinfo;
    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(buffer,80,"%Y-%m-%d-%H-%M-%S",timeinfo);
    std::string cpp_time = buffer;
    return cpp_time;
}

Data_FD::Data_FD(std::string path) : Path_FD(path) {
    fd = open_file();
}

int Data_FD::open_file() {
    if ((fd = open(path.c_str(), O_CREAT | O_RDWR | O_APPEND, 0644)) == -1) {
        return -1;
    }
    return fd;
}

#ifndef ENABLE_TESTING

int main(int argc, char* argv[]) {
    std::string filepath = getenv("HOME");
    filepath += "/Robosub/Data/";
    filepath += Data_Logger::get_current_time();
    std::unique_ptr<FD_Interface> drr_fd = std::make_unique<Data_FD>(filepath + "-dvl-drr.csv");
    std::unique_ptr<FD_Interface> vr_fd = std::make_unique<Data_FD>(filepath + "-dvl-vr.csv");
    std::unique_ptr<FD_Interface> imu_fd = std::make_unique<Data_FD>(filepath + "-imu.csv");

    rclcpp::init(argc, argv);
    auto data_logger = std::make_shared<Data_Logger>();
    rclcpp::spin(data_logger);
    
    rclcpp::shutdown();
    
    return 0;
}
#endif // ENABLE_TESTING

