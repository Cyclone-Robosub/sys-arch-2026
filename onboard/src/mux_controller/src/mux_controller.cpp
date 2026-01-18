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
    if (mode == current_control_mode || no_heartbeat) {
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

/*
 * For ANSI escape sequences, see: https://gist.github.com/ConnerWill/d4b6c776b509add763e17f9f113fd25b
*/

void Mux_Controller::clear_display() {
    printf("\x1B[2J\x1B[H");
}

void Mux_Controller::refresh_display() {
    tcflush(STDIN_FILENO, TCIFLUSH);
    current_input = "";
    clear_display();
    if (no_heartbeat) {
        write(STDOUT_FILENO, "\x1B[5m", 4); // set blinking
        write(STDOUT_FILENO, "\x1B[1;39m", 7); // set bold
        printf("====== No heartbeat detected from Mux! ======\n\n");
        write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
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

void Mux_Controller::backspace() {
    int orig_pos = cursor_pos;
    write(STDOUT_FILENO, "\x1B[1D", 4); // move left to prepare for delete
    while (cursor_pos < num_read) {
        char old_val = current_input[cursor_pos];
        current_input[cursor_pos - 1] = old_val;
        printf("%c", old_val);
        fflush(stdout);
        (cursor_pos)++;
    }
    write(STDOUT_FILENO, " ", 1);
    current_input.pop_back();
    while (cursor_pos >= orig_pos) {
        (cursor_pos)--;
        write(STDOUT_FILENO, "\x1B[1D", 4);
    }
    (num_read)--;
}

void Mux_Controller::process_input() {
    cursor_pos = 0;
    num_read = 0;
    int c = 0;
    current_input = "";
    while (true) {
        while (read(STDIN_FILENO, &c, 1) != 0) {
            if ((c >= 32 && c <= 126) || c == '\n') {
                cursor_pos++;
                num_read++;
                current_input.push_back((char)c);
                printf("%c", c);
                fflush(stdout);
                if (c == '\n') {
                    return;
                }
            }
            if (c == 127 && cursor_pos > 0) {
                backspace();
            }
            if (c == 27) {
                read(STDIN_FILENO, &c, 1);
                read(STDIN_FILENO, &c, 1);
                if (c == 51) { // delete key
                    read(STDIN_FILENO, &c, 1); // clear extra identifier
                    if (cursor_pos < num_read) {
                        write(STDOUT_FILENO, "\x1B[1C", 4);
                        cursor_pos++;
                        backspace();
                    }
                }
                else { // direction key
                    if (c == 65) { // up
                        // do nothing
                    }
                    if (c == 66) { // down
                        // do nothing
                    }
                    if (c == 67 && cursor_pos < num_read) { // right
                        write(STDOUT_FILENO, "\x1B[1C", 4);
                        cursor_pos++;
                    }
                    if (c == 68 && cursor_pos > 0) { // left
                        write(STDOUT_FILENO, "\x1B[1D", 4);
                        cursor_pos--;
                    }
                }
            }
        }
    }
}

void Mux_Controller::work_loop() {
    char mode = 0;
    int string_index = 0;

    while (rclcpp::ok()) {
        process_input();
        mode = current_input[0];
        mode = tolower(mode);

        if (current_input.size() < 2) {
            printf("Invalid command. Try again: ");
            fflush(stdout);
            continue; 
        }

        string_index = 1;
        if (mode == 'e' || mode == 'q') {
            break;
        }
        if (current_input[string_index] != '\n' || (mode != '0' && mode != '1')) {
            printf("Invalid command. Try again: ");
            fflush(stdout);
            while (current_input[string_index] != '\n') {
                string_index++;
            }
            continue;
        }
        
        set_mux_mode((bool)(mode - '0'));
    }
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