#include "mux_controller.hpp"

using namespace std::chrono_literals;

Mux_Controller::Mux_Controller() : Node("mux_controller") {
    current_control_mode_subscriber = this->create_subscription<std_msgs::msg::Bool>("current_mode", 10, 
        std::bind(&Mux_Controller::control_mode_callback, this, std::placeholders::_1));
    heartbeat_subscription = this->create_subscription<std_msgs::msg::Bool>("mux_heartbeat", 10, 
        std::bind(&Mux_Controller::mux_heartbeat_received_callback, this, std::placeholders::_1));
    
    heartbeat_timer = this->create_wall_timer(500ms, 
            std::bind(&Mux_Controller::heartbeat_check_callback, this)); // heartbeat timer    

    client = this->create_client<std_srvs::srv::SetBool>("control_mode");
    force_pub = this->create_client<std_srvs::srv::SetBool>("force_pub");
    
    refresh_display();
}

void Mux_Controller::get_mux_mode_now() {
    std::shared_ptr<std_srvs::srv::SetBool::Request> request = std::make_shared<std_srvs::srv::SetBool::Request>();
    request->data = true;
    force_pub->async_send_request(request);
}

void Mux_Controller::set_mux_mode(bool mode) {
    if (mode == current_control_mode) {
        refresh_display();
        return;
    }
    std::shared_ptr<std_srvs::srv::SetBool::Request> request = std::make_shared<std_srvs::srv::SetBool::Request>();
    request->data = mode;
    client->async_send_request(request);
}

void Mux_Controller::mux_heartbeat_received_callback(std_msgs::msg::Bool::UniquePtr heartbeat) {
    most_recent_heartbeat = std::chrono::steady_clock::now();
    if (no_heartbeat) {
        no_heartbeat = false; // If we just received a heartbeat, then we certainly have a heartbeat!
        get_mux_mode_now();
        refresh_display();
    }
    (void)heartbeat; // stop compiler complaining
}

void Mux_Controller::heartbeat_check_callback() {
    auto current_time = std::chrono::steady_clock::now();
    if (current_time - most_recent_heartbeat > 1s) {
        if (!no_heartbeat) {
            no_heartbeat = true;
            refresh_display();
        }
    }
    else {
        no_heartbeat = false;
    }
}

void Mux_Controller::control_mode_callback(std_msgs::msg::Bool::UniquePtr msg) {
    current_control_mode = msg->data;
    refresh_display();
}

void Mux_Controller::clear_display() {
    printf("\x1B[2J\x1B[H");
}

void Mux_Controller::refresh_display() {
    tcflush(STDIN_FILENO, TCIFLUSH);
    clear_display();
    if (no_heartbeat) {
        printf("====== No heartbeat detected from Mux! ======\n\n");
    }
    else {
        printf("Current mode is: %s\n\n", current_control_mode ? "matlab (ctrl)" : "cli" );
    }
    printf("Enter the control mode you'd like to switch to.\n");
    printf("[0]: CLI mode\n");
    printf("[1]: Matlab mode\n");
    printf("[E]: Exit\n");
    printf("Mode: ");
    fflush(stdout);
}

void Mux_Controller::process_input() {
    int cursor_pos = 0;
    int num_read = 0;
    int c = 0;
    while (true) {
        while (read(STDIN_FILENO, &c, 1) != 0) {
            if (c == '\n') {
                return;
            }
            if (c >= 32 && c <= 126) {
                cursor_pos++;
                num_read++;
                // append to record
                printf("%c", c);
                fflush(stdout);
            }
            if (c == 127 && cursor_pos > 0) {
                // remove from record
                if (num_read == cursor_pos) { // end of string
                    printf("\b \b");
                }
                else {
                    // shift all the characters along
                }
                
                fflush(stdout);
                cursor_pos--;
                num_read--;
            }
            if (c == 27) {
                read(STDIN_FILENO, &c, 1);
                read(STDIN_FILENO, &c, 1);
                if (c == 51) { // delete key
                    read(STDIN_FILENO, &c, 1); // clear extra identifier
                    // delete
                    cursor_pos--;
                    num_read--;
                }
                else { // direction key
                    if (c == 65) { // up
                        // do nothing
                    }
                    if (c == 66) { // down
                        // do nothing
                    }
                    if (c == 67) { // right
                        // go right
                    }
                    if (c == 68 && cursor_pos > 0) { // left
                        write(STDOUT_FILENO, "\b", 1);
                        cursor_pos--;
                    }
                }
            }
        }
    }
    
}

void Mux_Controller::work_loop() {
    // while (no_heartbeat && rclcpp::ok()) {
    //     // wait until we get a heartbeat
    // }
    // get_mux_mode_now();

    // char mode = 0;
    // char should_be_newline = 0;

    // while (rclcpp::ok()) {
    //     read(STDIN_FILENO, &mode, 1);
    //     read(STDIN_FILENO, &should_be_newline, 1);
    //     mode = tolower(mode);
    //     if (mode == 'e' || mode == 'q') {
    //         break;
    //     }
    //     if (should_be_newline != '\n' || (mode != '0' && mode != '1')) {
    //         printf("Invalid command. Try again: ");
    //         while (should_be_newline != '\n') {
    //             read(STDIN_FILENO, &should_be_newline, 1);
    //         }
    //         continue;
    //     }
        
    //     set_mux_mode((bool)(mode - '0'));
    // }
    process_input();
}

int main(int argc, char* argv[]) {    
    rclcpp::init(argc, argv);
    auto mux_controller = std::make_shared<Mux_Controller>();
    
    std::thread ros_thread([&]() { // Needs to be seperate thread so that input loop can run
        rclcpp::spin(mux_controller);
    });

    struct termios orig_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);  // no line buffering or echoing
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    mux_controller->work_loop();
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);

    rclcpp::shutdown();
    ros_thread.join();

    Mux_Controller::clear_display();
    
    
    return 0;
}