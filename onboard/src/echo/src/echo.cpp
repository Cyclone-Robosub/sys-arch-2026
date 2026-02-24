#include "echo.hpp"
#include <fcntl.h> // for fd stuff
#include <chrono>

using namespace std::chrono_literals;

Echo::Echo(std::unique_ptr<FD_Interface> fd) : 
    Node("echo"),
    log_fd(std::move(fd)),
    state(Get_Command),
    log_active(false)
     {

    pwm_received_subscription = this->create_subscription<custom_interfaces::msg::Pwms>(
        "pwm_cmd", 10, 
        std::bind(&Echo::pwm_received_subscription_callback, this, std::placeholders::_1));
    
    pwm_publisher = this->create_publisher<custom_interfaces::msg::Pwms>("pwm_echo", 10);

    heartbeat_publisher = this->create_publisher<std_msgs::msg::Bool>("echo_heartbeat", 10);
    heartbeat_timer = this->create_wall_timer(500ms, 
            std::bind(&Echo::heartbeat_callback, this));
}

void Echo::pwm_received_subscription_callback(custom_interfaces::msg::Pwms::UniquePtr pwms_msg) {
    if (log_active) {
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
    lseek(log_fd->get_read_fd(), 0, SEEK_SET);
    while (true) {
        while (std::chrono::steady_clock::now() - current_time < 0.01s) {} // publish at 100 hz
        ssize_t num_read = read(log_fd->get_read_fd(), line, 41);
        if (num_read == 0) {
            RCLCPP_INFO(this->get_logger(), "Finished reading from file.");
            return;
        } else if (num_read < 41) {
            RCLCPP_WARN(this->get_logger(), "Unable to read from PWM log file");
        }

        pwms = parse_log_line(line);

        msg.pwms = pwms;
        pwm_publisher->publish(msg);
        current_time = std::chrono::steady_clock::now();
    }
}

void Echo::heartbeat_callback() {
    std_msgs::msg::Bool msg;
    heartbeat_publisher->publish(msg);
}

std::array<int32_t,8> Echo::parse_log_line(char* line) { // TODO: Do error checking (currently assumes perfectly formatted file)
    std::array<int32_t,8> pwms;
    size_t start_index = 41 - 6; // index of last PWM
    for (int i = 7; i >= 0; i--) {
        pwms[i] = std::stoi(line + start_index);
        line[start_index - 1] = '\0';
        start_index -= 5;
    }
    return pwms;
}

void Echo::logging_loop() {
    printf("Writing to file ~/LOG.txt...\n");
    printf("Type 'q' when you are done: ");
    log_active = true;
    while (true) {
        char quit = '\0';
        char should_be_newline;
        scanf("%c", &quit);
        scanf("%c", &should_be_newline);
        quit = tolower(quit);
        while (should_be_newline != '\n') {
            scanf("%c", &should_be_newline);
            quit = '\0'; // so we try again with an invalid input error
        }
        if (quit == 'q') {
            log_active = false;
            return;
        } else {
            std::cout << "Invalid input. Try again: ";
        }
    }
}

State Echo::get_next_state() {
    while (true) {
        char new_mode = '\0';
        char should_be_newline;
        printf("Select Mode: W for write, R for read, Q for quit: ");
        scanf("%c", &new_mode);
        scanf("%c", &should_be_newline);
        new_mode = tolower(new_mode);
        while (should_be_newline != '\n') {
            scanf("%c", &should_be_newline);
            new_mode = '\0'; // so we try again with an invalid mode error
        }
        if (new_mode == 'w') {
            return Write_Log;
        } else if (new_mode == 'r') {
            return Read_Log;
        } else if (new_mode == 'q' || new_mode == 'e') {
            return Exit;
        } else {
            std::cout << "Invalid mode. Try again!\n";
        }
    }
}

void Echo::work_loop() {
    while (true) {
        switch (state) {
            case Get_Command:
                state = get_next_state();
                break;
            case Write_Log:
                logging_loop();
                state = Get_Command;
                break;
            case Read_Log:
                echo_pwms();
                state = Get_Command;
                break;
            case Exit:
            default:
                return;
        }
    }
}

Log_FD::Log_FD(std::string path) : Path_FD(path) {
    fd = open_file();
}

int Log_FD::open_file() {
    if ((fd = open(path.c_str(), O_CREAT | O_RDWR | O_APPEND, 0644)) == -1) {
        return -1;
    }
    return fd;
}

#ifndef ENABLE_TESTING

int main(int argc, char* argv[]) {
    std::string filepath = getenv("HOME");
    filepath += "/LOG.txt";
    std::unique_ptr<FD_Interface> log_fd = std::make_unique<Log_FD>(filepath);

    rclcpp::init(argc, argv);
    auto echo = std::make_shared<Echo>(std::move(log_fd));

    std::thread ros_thread([&]() { // Needs to be seperate thread so that we can get user input from main()
        rclcpp::spin(echo);
    });

    echo->work_loop();
    
    rclcpp::shutdown();
    ros_thread.join();
    
    return 0;
}
#endif // ENABLE_TESTING

