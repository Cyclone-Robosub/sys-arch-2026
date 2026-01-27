#include "thrust_interface.hpp"
#include <vector>
#include <string>
/* For serial */
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
/* For serial */
#include <signal.h>

using namespace std::chrono_literals;
using namespace rclcpp;

Thrust_Interface::Thrust_Interface(std::vector<int> thrusters, int pico_fd, 
                                   int min_pwm, int max_pwm) : 
    Node("thrust_interface"), 
    thrusters(thrusters), 
    pico_fd(pico_fd),
    min_pwm(min_pwm), 
    max_pwm(max_pwm),
    no_heartbeat(true),
    write_failure_count(0)
     {
    
    pwm_received_subscription = this->create_subscription<custom_interfaces::msg::Pwms>(
        "pwm_cmd", 10, 
        std::bind(&Thrust_Interface::pwm_received_subscription_callback, this, std::placeholders::_1));

    heartbeat_subscription = this->create_subscription<std_msgs::msg::Bool>("mux_heartbeat", 10, 
            std::bind(&Thrust_Interface::mux_heartbeat_received_callback, this, std::placeholders::_1));
    
    if (pico_fd < 0) {
        RCLCPP_ERROR(this->get_logger(), "Invalid file descriptor provided: %d", pico_fd);
        exit(42);
    }
    
    heartbeat_timer = this->create_wall_timer(500ms, 
            std::bind(&Thrust_Interface::heartbeat_callback, this)); // heartbeat timer
    
    write_failure_exit = false;
}
    
void Thrust_Interface::pwm_received_subscription_callback(custom_interfaces::msg::Pwms::UniquePtr pwms_msg) {
    if (no_heartbeat) {
        return;
    }
    std::array<int, 8> pwms = pwms_msg->pwms;
    
    for (int i = 0; i < 8; i++) {
        if (pwms[i] != 0) {
            pwms[i] = std::max(pwms[i], min_pwm);
            pwms[i] = std::min(pwms[i], max_pwm);
        }
        send_pwm_to_pico(thrusters[i], pwms[i]);
    }
}

void Thrust_Interface::mux_heartbeat_received_callback(std_msgs::msg::Bool::UniquePtr heartbeat) {
    most_recent_heartbeat = std::chrono::steady_clock::now();
    if (no_heartbeat) {
        no_heartbeat = false; // If we just received a heartbeat, then we certainly have a heartbeat!
    }
    (void)heartbeat; // stop compiler complaining
}

void Thrust_Interface::evaluate_mux_heartbeat_freshness() {
    auto current_time = std::chrono::steady_clock::now();
    if (current_time - most_recent_heartbeat > 1s) {
        RCLCPP_INFO(this->get_logger(), "Didn't get heartbeat from mux. Sending stop command.");
        no_heartbeat = true;
        for (int i = 0; i < 8; i++) {
            send_pwm_to_pico(thrusters[i], 1500);
        }
    }
    else {
        no_heartbeat = false;
    }
}
void Thrust_Interface::send_heartbeat_to_pico() {
    std::string serial_message = "ping\n";
    int length = serial_message.size();
    
    serial_mutex.lock();
    ssize_t bytes_written = write(pico_fd, serial_message.c_str(), length);
    serial_mutex.unlock();
    
    if (bytes_written != length) {
        RCLCPP_WARN(this->get_logger(), 
                    "Failed to ping Pico (wrote %zd/%d bytes)", 
                    bytes_written, length);
        write_failure_count++;
    }
    if (write_failure_count >= 100) {
        write_failure_exit = true;
        RCLCPP_ERROR(this->get_logger(), "Exiting thruster_interface due to write issues.");
        raise(SIGINT);
    }
}

void Thrust_Interface::heartbeat_callback() {
    send_heartbeat_to_pico();
    evaluate_mux_heartbeat_freshness();
}

void Thrust_Interface::send_pwm_to_pico(int thruster, int pwm) {
    std::string serial_message = "Set " + std::to_string(thruster) + " PWM " + std::to_string(pwm) + "\n";
    int length = serial_message.size();
    
    serial_mutex.lock();
    ssize_t bytes_written = write(pico_fd, serial_message.c_str(), length);
    serial_mutex.unlock();
    
    if (bytes_written != length) {
        RCLCPP_WARN(this->get_logger(), 
                    "Failed to write complete message for thruster %d (wrote %zd/%d bytes)", 
                    thruster, bytes_written, length);
        write_failure_count++;
    }
    if (write_failure_count >= 100) {
        write_failure_exit = true;
        RCLCPP_ERROR(this->get_logger(), "Exiting thruster_interface due to write issues.");
        raise(SIGINT);
    }
}

int Thrust_Interface::open_pico_serial(std::string pico_path) {
    struct termios options;
    speed_t baud = 115200;
    int status, fd;
    
    if ((fd = open(pico_path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) == -1) {
        return -1;
    }
    
    fcntl(fd, F_SETFL, O_RDWR);
    
    // Get and modify current options:
    tcgetattr(fd, &options);
    cfmakeraw(&options);
    cfsetispeed(&options, baud);
    cfsetospeed(&options, baud);
    
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    
    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 1;  // 1/10 (1 decisecond)
    
    tcsetattr(fd, TCSANOW, &options);
    
    ioctl(fd, TIOCMGET, &status);
    status |= TIOCM_DTR;
    status |= TIOCM_RTS;
    ioctl(fd, TIOCMSET, &status);
    
    usleep(100000);  // 100ms
    
    return fd;
}

#ifndef ENABLE_TESTING

int main(int argc, char* argv[]) {
    std::vector<int> thrusters = {8, 9, 6, 7, 13, 11, 12, 10};
    int fd = Thrust_Interface::open_pico_serial("/dev/serial/by-id/usb-MicroPython_Board_in_FS_mode_7327d9a2ecd31892-if00");
    rclcpp::init(argc, argv);
    auto thrust_interface = std::make_shared<Thrust_Interface>(thrusters, fd, 1200, 1800);
    rclcpp::spin(thrust_interface);
    
    /* Some level of automatic recovery if we lose the Pico for a short amount of time */
    while (Thrust_Interface::write_failure_exit) {
        usleep(100000); //wait 0.1 seconds before looping to avoid excessive CPU usage
        RCLCPP_WARN(thrust_interface->get_logger(), "Attempting to restart thruster_interface.");
        fd = Thrust_Interface::open_pico_serial("/dev/serial/by-id/usb-MicroPython_Board_in_FS_mode_7327d9a2ecd31892-if00");
        if (fd < 0) { // Still can't connect to Pico...
            RCLCPP_WARN(thrust_interface->get_logger(), "Unable to connect to Pico.");
            continue;
        }
        rclcpp::shutdown();
        rclcpp::init(argc, argv);
        auto thrust_interface = std::make_shared<Thrust_Interface>(thrusters, fd, 1200, 1800);
        rclcpp::spin(thrust_interface);
    }

    rclcpp::shutdown();

    if (fd >= 0) {
        close(fd);
    }
    
    return 0;
}
#endif

