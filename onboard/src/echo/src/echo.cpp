#include "echo.hpp"
#include <fcntl.h> // for fd stuff
#include <chrono>

using namespace std::chrono_literals;

Echo::Echo(std::unique_ptr<FD_Interface> fd) : 
    Node("echo"),
    log_fd(std::move(fd)),
    mode(None)
     {

    pwm_received_subscription = this->create_subscription<custom_interfaces::msg::Pwms>(
        "pwm_cmd", 10, 
        std::bind(&Echo::pwm_received_subscription_callback, this, std::placeholders::_1));
    
    pwm_cmd_publisher = this->create_publisher<custom_interfaces::msg::Pwms>("pwm_cmd", 10);
}

void Echo::set_mode(Use_Mode mode) {
    this-> mode = mode;
    if (mode == Read) { // TODO: move this somewhere more sensible? Some kind of state machine maybe...
        echo_pwms();
    }
}

void Echo::pwm_received_subscription_callback(custom_interfaces::msg::Pwms::UniquePtr pwms_msg) {
    if (mode == Write) {
        log_pwms(pwms_msg->pwms);
    }
}

void Echo::log_pwms(std::array<int32_t,8> pwms) {
    char log_message[5] = {0}; // PWM = 4 chars, space = 1 char
    for (auto pwm : pwms) {
        sprintf(log_message, "%d ", pwm);
        if (write(log_fd->get_write_fd(), log_message, 5) < 5) {
            RCLCPP_WARN(this->get_logger(), "Unable to write to PWM log file");
        }
    }
    if (write(log_fd->get_write_fd(), "\n",  1) < 1) {
        RCLCPP_WARN(this->get_logger(), "Unable to write to PWM log file");
    }
}

void Echo::echo_pwms() { // TODO: Do error checking (currently assumes perfectly formatted file)
    auto current_time = std::chrono::steady_clock::now();
    std::array<int32_t,8> pwms;
    custom_interfaces::msg::Pwms msg;
    char line[42] = {0}; // 4 * 8 pwms = 32, 8 spaces, 1 newline, 1 null character
    while (true) {
        while (std::chrono::steady_clock::now() - current_time < 0.01s) {} // publish at 100 hz
        ssize_t num_read = read(log_fd->get_read_fd(), line, 41);
        if (num_read == 0) {
            RCLCPP_INFO(this->get_logger(), "Finished reading from file. Exiting...");
            exit(0);
        } else if (num_read < 41) {
            RCLCPP_WARN(this->get_logger(), "Unable to read from PWM log file");
        }

        pwms = parseLine(line);

        msg.pwms = pwms;
        pwm_cmd_publisher->publish(msg);
        current_time = std::chrono::steady_clock::now();
    }
}

std::array<int32_t,8> Echo::parseLine(char* line) { // TODO: Do error checking (currently assumes perfectly formatted file)
    std::array<int32_t,8> pwms;
    size_t start_index = 41 - 6; // index of last PWM
    for (int i = 7; i >= 0; i--) {
        pwms[i] = std::stoi(line + start_index);
        line[start_index - 1] = '\0';
        start_index -= 5;
    }
    return pwms;
}

#ifndef ENABLE_TESTING

int main(int argc, char* argv[]) {
    std::string filepath = getenv("HOME");
    filepath += "/LOG.txt";
    int log_fd = open(filepath.c_str(), O_CREAT | O_RDWR | O_APPEND, 0644);
    std::unique_ptr<FD_Interface> fd = std::make_unique<Direct_FD>(log_fd, log_fd);

    rclcpp::init(argc, argv);
    auto echo = std::make_shared<Echo>(std::move(fd));

    std::thread ros_thread([&]() { // Needs to be seperate thread so that we can get user input from main()
        rclcpp::spin(echo);
    });
    while (true) {
        char mode = '\0'; // TODO: Error checking
        printf("Select Mode: W for write, R for read, Q for quit: ");
        scanf("%c", &mode);
        getchar(); //eat newline
        mode = tolower(mode);
        if (mode == 'w') {
            echo->set_mode(Write);
        } else if (mode == 'r') {
            echo->set_mode(Read);
        } else if (mode == 'q') {
            break;
        } else {
            std::cerr << "Invalid mode, not writing data!\n";
        }
    }

    
    rclcpp::shutdown();
    ros_thread.join();
    
    return 0;
}
#endif // ENABLE_TESTING

