#include "tui.hpp"
#include <sys/wait.h>

using namespace std::chrono_literals;

Dashboard::Dashboard(std::unique_ptr<TUI_Interface> tui) : Node("tui"), tui(std::move(tui)) {
    // Heartbeats
    thrust_interface_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("thrust_interface_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    mux_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("mux_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    ctrl_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("ctrl_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    cli_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("cli_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    echo_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("echo_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    dvl_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("dvl_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    joystick_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("joystick_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    
    // Data
    pwm_cmd_subscription = this->create_subscription<std_msgs::msg::Empty>("thrust_interface_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    pwm_ctrl_subscription = this->create_subscription<std_msgs::msg::Empty>("mux_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    pwm_cli_subscription = this->create_subscription<std_msgs::msg::Empty>("ctrl_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    pwm_echo_subscription = this->create_subscription<std_msgs::msg::Empty>("cli_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    dvl_drr_subscription = this->create_subscription<std_msgs::msg::Empty>("dvl_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    dvl_vr_subscription = this->create_subscription<std_msgs::msg::Empty>("dvl_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    current_control_mode_subscription = this->create_subscription<std_msgs::msg::UInt8>("current_mode", 10, 
        std::bind(&Dashboard::control_mode_callback, this, std::placeholders::_1));

    heartbeat_timer = this->create_wall_timer(500ms, 
            std::bind(&Dashboard::heartbeat_check_callback, this));

    client = this->create_client<custom_interfaces::srv::ControlMode>("control_mode");
    force_pub = this->create_client<std_srvs::srv::SetBool>("force_pub");
    
    refresh_display();
}

void Dashboard::get_mux_mode_now() {
    std::shared_ptr<std_srvs::srv::SetBool::Request> request = std::make_shared<std_srvs::srv::SetBool::Request>();
    request->data = true;
    force_pub->async_send_request(request);
}

void Dashboard::mux_heartbeat_received_callback(std_msgs::msg::Empty::UniquePtr heartbeat) {
    most_recent_heartbeat = std::chrono::steady_clock::now();
    if (no_heartbeat) {
        no_heartbeat = false; // If we just received a heartbeat, then we certainly have a heartbeat!
        get_mux_mode_now();
        refresh_display();
    }
    (void)heartbeat; // stop compiler complaining
}

void Dashboard::heartbeat_check_callback() {
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

void Dashboard::control_mode_callback(std_msgs::msg::UInt8::UniquePtr msg) {
    current_control_mode = msg->data;
    refresh_display();
}

void Dashboard::work_loop() {
    // char mode = 0;
    int string_index = 0;

    tui->init_terminal();

    while (rclcpp::ok()) {
        // tui->process_input();
        tui->freeze_display();
        // std::string current_input = tui->get_current_input();
        // mode = current_input[0];
        // mode = tolower(mode);

        // if (current_input.size() < 2) {
        //     printf("Invalid command. Try again: ");
        //     fflush(stdout);
        //     tui->unfreeze_display();
        //     continue; 
        // }

        // string_index = 1;
        // if (mode == 'e' || mode == 'q') {
        //     tui->unfreeze_display();
        //     break;
        // }
        // if (current_input[string_index] != '\n' || (mode != '0' && mode != '1' && mode != '2' && mode != '3')) {
        //     printf("Invalid command. Try again: ");
        //     fflush(stdout);
        //     while (current_input[string_index] != '\n') {
        //         string_index++;
        //     }
        //     tui->unfreeze_display();
        //     continue;
        // }
        tui->unfreeze_display();
    }
    tui->restore_terminal();
    tui->clear_display();
}

void Dashboard::refresh_display() {
    tui->refresh_display(2, no_heartbeat, current_control_mode);
}

// TODO: make member functions

void jump_to_column(int col_number) {
    std::string column_string = "\x1B[" + std::to_string(col_number) + "G";
    write(STDOUT_FILENO, column_string.c_str(), column_string.length());
}

void reset_cursor_pos() {
    write(STDOUT_FILENO, "\x1B[H", 3);
}

void write_header(std::string header, int col_number) {
    jump_to_column(col_number);
    write(STDOUT_FILENO, "\x1B[1m", 4); // set bold
    printf("%s\n", header.c_str());
    write(STDOUT_FILENO, "\x1B[22m", 5); // unset bold
    jump_to_column(col_number);
}

void display_critical_status(bool heartbeat, int col_number) {
    jump_to_column(col_number);
    if (!heartbeat) {
        write(STDOUT_FILENO, "\x1B[5;7m", 6); // blinking, inverted
        write(STDOUT_FILENO, "\x1B[31;107m", 9); // set red foreground, white background
        printf("== No heartbeat detected! ==\n");
        write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
    } else {
        printf("== OK ==\n");
    }
    jump_to_column(col_number);
}

void display_noncritical_status(bool heartbeat, int col_number) {
    jump_to_column(col_number);
    if (!heartbeat) {
        write(STDOUT_FILENO, "\x1B[5;7m", 6); // blinking, inverted
        printf("== No heartbeat detected! ==\n");
        write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
    }
    else {
        printf("== OK ==\n");
    }
    jump_to_column(col_number);
}

void display_escalatable_status(int current_mode, int critical_mode, bool heartbeat, int col_number) {
    if (current_mode == critical_mode) {
        display_critical_status(heartbeat, col_number);
    }
    else {
        display_noncritical_status(heartbeat, col_number);
    }
}

/* Note: this function returns cursor to its original position so sub-columns can be next to each other*/
void display_pwms(int* pwms, int col_number) {
    write(STDOUT_FILENO, "\x1B[s", 3); // Save cursor position
    printf("\n");
    if (pwms[0] == 0) { // no pwms to display
        for (int i = 0; i < 8; i ++) {
            jump_to_column(col_number);
            printf("|\n");
        }
        write(STDOUT_FILENO, "\x1B[u", 3); // Restore cursor position
        return;
    }
    for (int i = 0; i < 8; i++) {
        jump_to_column(col_number);
        printf("| %d\n", pwms[i]);
    }
    write(STDOUT_FILENO, "\x1B[u", 3); // Restore cursor position
}

void fill_right_col(int col_number) {
    for (int i = 0; i < 9; i++) {
        jump_to_column(col_number);
        printf("|\n");
    }
}

void display_all_pwms(int* pwms_cmd, int* pwms_cli, int* pwms_ctrl, int* pwms_echo, int main_col, int sub_col_1, int sub_col_2, int sub_col_3) {
    printf("| - CMD - ");
    display_pwms(pwms_cmd, main_col);
    jump_to_column(sub_col_1);
    printf("| - CLI - ");
    display_pwms(pwms_cli, sub_col_1);
    jump_to_column(sub_col_2);
    printf("| - CTRL - ");
    display_pwms(pwms_ctrl, sub_col_2);
    jump_to_column(sub_col_3);
    printf("| - ECHO - |");
    display_pwms(pwms_echo, sub_col_3);
    fill_right_col(sub_col_3 + 11);
}

void display_connection_info(bool connection_ok, double seconds_since_ping, double ping_rtt, int col_number) {
    jump_to_column(col_number);
    if (!connection_ok) {
        write(STDOUT_FILENO, "\x1B[5;7m", 6); // blinking, inverted
        write(STDOUT_FILENO, "\x1B[31;107m", 9); // set red foreground, white background
        printf("== No robot connection! Check ethernet cable. ==\n");
        write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
    }
    else {
        printf("Most recent ping: rtt %.3lfms | %.3lf seconds since last ping.\n", ping_rtt, seconds_since_ping);
    }
}

void display_drr(int col_number) {
    jump_to_column(col_number);
    printf("TODO DRR\n");
}

void display_vr(int col_number) {
    jump_to_column(col_number);
    printf("TODO VR\n");
}

// TODO: run in seperate thread
std::string get_ping() {
    int pipe_fds[2];
    pipe(pipe_fds); // [0] = read end, [1] = write end
    int pid = fork();
    if (pid > 0) { // Parent
        char buf[512] = {0};
        int status;
        waitpid(pid, &status, 0);
        if (status != 0) {
            return "error";
        }
        read(pipe_fds[0], buf, 512);
        return buf;
    } else { // Child
        dup2(pipe_fds[1], STDOUT_FILENO);
        execlp("ping", "ping", "-c 1", "localhost", NULL);
        return "error"; // should never get here
    }
}

void Dashboard_TUI::display_tui(va_list args) {
    // TODO: get these values from args list
    int current_mux_mode = 2;
    bool thrust_interface_heartbeat = false;
    bool mux_heartbeat = false;
    bool ctrl_heartbeat = true;
    bool cli_heartbeat = false;
    bool echo_heartbeat = false;
    bool dvl_heartbeat = false;
    bool joystick_heartbeat = false;
    int pwms_cmd[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
    int pwms_cli[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
    int pwms_ctrl[] = {1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};
    int pwms_echo[] = {0, 0, 0, 0, 0, 0, 0, 0};
    bool ping_ok = true;
    double ping_rtt = 0.244;
    double seconds_since_ping = 0.1;

    int first_col = 0;
    int second_col = 35;

    write_header("thrust_interface", first_col);
    display_critical_status(thrust_interface_heartbeat, first_col);
    printf("\n");

    write_header("soft_mux", first_col);
    display_critical_status(mux_heartbeat, first_col);
    printf("\n");

    write_header("ctrl", first_col);
    display_escalatable_status(current_mux_mode, 1, ctrl_heartbeat, first_col);
    printf("\n");

    write_header("cli", first_col);
    display_escalatable_status(current_mux_mode, 2, cli_heartbeat, first_col);
    printf("\n");

    write_header("echo", first_col);
    display_escalatable_status(current_mux_mode, 3, echo_heartbeat, first_col);
    printf("\n");

    write_header("dvl", first_col);
    display_critical_status(dvl_heartbeat, first_col);
    display_vr(first_col);
    display_drr(first_col);
    printf("\n");

    write_header("Robot Connection Status", first_col);
    display_connection_info(ping_ok, ping_rtt, seconds_since_ping, first_col);
    
    reset_cursor_pos();

    write_header("pwms", second_col);
    display_all_pwms(pwms_cmd, pwms_cli, pwms_ctrl, pwms_echo, second_col, 45, 55, 66);
    printf("\n");

    printf("\n");
    write_header("Joystick", second_col);
    display_escalatable_status(current_mux_mode, 1, joystick_heartbeat, second_col);
    printf("\n");

    

    // bool no_heartbeat = (bool)va_arg(args, int);
    // int current_control_mode = va_arg(args, int);
    // va_end(args);
    // if (no_heartbeat) {
    //     write(STDOUT_FILENO, "\x1B[5m", 4); // set blinking
    //     write(STDOUT_FILENO, "\x1B[1;7m", 6); // set bold, inverted
    //     printf("====== No heartbeat detected from Mux! ======\n\n");
    //     write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
    // }
    // else {
    //     printf("Current mode is: ");
    //     switch (current_control_mode) {
    //         case 0:
    //             printf("disabled");
    //             break;
    //         case 1:
    //             printf("cli");
    //             break;
    //         case 2:
    //             printf("matlab (ctrl)");
    //             break;
    //         case 3:
    //             printf("echo (playback)");
    //             break;
    //     }
    //     printf("\n\n");
    // }
    // printf("Enter the control mode you'd like to switch to.\n");
    // printf("[0]: Disabled\n");
    // printf("[1]: CLI mode\n");
    // printf("[2]: Matlab mode\n");
    // printf("[3]: Echo mode\n");
    // printf("[E]: Exit\n");
    // printf("Mode: ");
    fflush(stdout);
}

int main(int argc, char* argv[]) {    
    rclcpp::init(argc, argv);
    std::unique_ptr<TUI_Interface> tui = std::make_unique<Dashboard_TUI>();
    auto dashboard = std::make_shared<Dashboard>(std::move(tui));
    
    std::thread ros_thread([&]() { // Needs to be seperate thread so that input loop can run
        rclcpp::spin(dashboard);
    });

    dashboard->work_loop();

    rclcpp::shutdown();
    ros_thread.join();
    
    return 0;
}
