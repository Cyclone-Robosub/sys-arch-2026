#include "tui.hpp"

using namespace std::chrono_literals;

Dashboard::Dashboard(std::unique_ptr<TUI_Interface> tui) : Node("tui"), tui(std::move(tui)) {
    // Heartbeats
    thrust_interface_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("thrust_interface_heartbeat", 10, 
        std::bind(&Dashboard::thrust_interface_heartbeat_received_callback, this, std::placeholders::_1));
    mux_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("mux_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    cli_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("cli_heartbeat", 10, 
        std::bind(&Dashboard::cli_heartbeat_received_callback, this, std::placeholders::_1));
    ctrl_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("ctrl_heartbeat", 10, 
        std::bind(&Dashboard::ctrl_heartbeat_received_callback, this, std::placeholders::_1));
    echo_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("echo_heartbeat", 10, 
        std::bind(&Dashboard::echo_heartbeat_received_callback, this, std::placeholders::_1));
    dvl_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("dvl_heartbeat", 10, 
        std::bind(&Dashboard::dvl_heartbeat_received_callback, this, std::placeholders::_1));
    joystick_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("joystick_heartbeat", 10, 
        std::bind(&Dashboard::joystick_heartbeat_received_callback, this, std::placeholders::_1));
    mission_manager_heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("mission_manager_heartbeat", 10, 
        std::bind(&Dashboard::mission_manager_heartbeat_received_callback, this, std::placeholders::_1));
    
    // Data
    pwm_cmd_subscription = this->create_subscription<custom_interfaces::msg::Pwms>("pwm_cmd", 10, 
        std::bind(&Dashboard::pwm_cmd_callback, this, std::placeholders::_1));
    pwm_cli_subscription = this->create_subscription<custom_interfaces::msg::Pwms>("pwm_cli", 10, 
        std::bind(&Dashboard::pwm_cli_callback, this, std::placeholders::_1));
    pwm_ctrl_subscription = this->create_subscription<custom_interfaces::msg::Pwms>("pwm_ctrl", 10, 
        std::bind(&Dashboard::pwm_ctrl_callback, this, std::placeholders::_1));
    pwm_echo_subscription = this->create_subscription<custom_interfaces::msg::Pwms>("pwm_echo", 10, 
        std::bind(&Dashboard::pwm_echo_callback, this, std::placeholders::_1));
    dvl_vr_subscription = this->create_subscription<custom_interfaces::msg::VR>("velocity_report", 10, 
        std::bind(&Dashboard::dvl_vr_callback, this, std::placeholders::_1));
    dvl_drr_subscription = this->create_subscription<custom_interfaces::msg::DRR>("dead_reck_report", 10, 
        std::bind(&Dashboard::dvl_drr_callback, this, std::placeholders::_1));
    current_control_mode_subscription = this->create_subscription<std_msgs::msg::UInt8>("current_mode", 10, 
        std::bind(&Dashboard::control_mode_callback, this, std::placeholders::_1));

    heartbeat_timer = this->create_wall_timer(17ms,
            std::bind(&Dashboard::heartbeat_check_callback, this)); // 60 hz
    
    clear_display_timer = this->create_wall_timer(5s,
            std::bind(&Dashboard::clear_display, this)); // Screen resizing, etc. will get taken care of every 5 seconds

    mux_client = this->create_client<custom_interfaces::srv::ControlMode>("control_mode");
    reset_drr_client = this->create_client<std_srvs::srv::Trigger>("reset_drr");
    reset_gyro_client = this->create_client<std_srvs::srv::Trigger>("reset_gyro");
    mission_manager_client = this->create_client<std_srvs::srv::Trigger>("ready_signal_service");
    force_pub = this->create_client<std_srvs::srv::SetBool>("force_pub");
    
    refresh_display();
}

void Dashboard::get_mux_mode_now() {
    std::shared_ptr<std_srvs::srv::SetBool::Request> request = std::make_shared<std_srvs::srv::SetBool::Request>();
    request->data = true;
    force_pub->async_send_request(request);
}

void Dashboard::heartbeat_check_callback() {
    auto current_time = std::chrono::steady_clock::now();
    thrust_interface_heartbeat = no_heartbeat(current_time, most_recent_thrust_interface_heartbeat);
    mux_heartbeat = no_heartbeat(current_time, most_recent_mux_heartbeat);
    cli_heartbeat = no_heartbeat(current_time, most_recent_cli_heartbeat);
    ctrl_heartbeat = no_heartbeat(current_time, most_recent_ctrl_heartbeat);
    echo_heartbeat = no_heartbeat(current_time, most_recent_echo_heartbeat);
    dvl_heartbeat = no_heartbeat(current_time, most_recent_dvl_heartbeat);
    joystick_heartbeat = no_heartbeat(current_time, most_recent_joystick_heartbeat);  
    mission_manager_heartbeat = no_heartbeat(current_time, most_recent_mission_manager_heartbeat); 
    refresh_display();
}

bool Dashboard::no_heartbeat(std::chrono::time_point<std::chrono::steady_clock> now, std::chrono::time_point<std::chrono::steady_clock> heartbeat_time) {
    return ((now - heartbeat_time) <= 1s);
}

void Dashboard::thrust_interface_heartbeat_received_callback(std_msgs::msg::Empty::UniquePtr heartbeat) {
    most_recent_thrust_interface_heartbeat = std::chrono::steady_clock::now();
    thrust_interface_heartbeat = true; // If we just received a heartbeat, then we certainly have a heartbeat!
    (void)heartbeat; // stop compiler complaining
}

void Dashboard::mux_heartbeat_received_callback(std_msgs::msg::Empty::UniquePtr heartbeat) {
    most_recent_mux_heartbeat = std::chrono::steady_clock::now();
    if (!mux_heartbeat) {
        mux_heartbeat = true; // If we just received a heartbeat, then we certainly have a heartbeat!
        get_mux_mode_now();
    }
    (void)heartbeat; // stop compiler complaining
}

void Dashboard::cli_heartbeat_received_callback(std_msgs::msg::Empty::UniquePtr heartbeat) {
    most_recent_cli_heartbeat = std::chrono::steady_clock::now();
    cli_heartbeat = true; // If we just received a heartbeat, then we certainly have a heartbeat!
    (void)heartbeat; // stop compiler complaining
}

void Dashboard::ctrl_heartbeat_received_callback(std_msgs::msg::Empty::UniquePtr heartbeat) {
    most_recent_ctrl_heartbeat = std::chrono::steady_clock::now();
    ctrl_heartbeat = true; // If we just received a heartbeat, then we certainly have a heartbeat!
    (void)heartbeat; // stop compiler complaining
}


void Dashboard::echo_heartbeat_received_callback(std_msgs::msg::Empty::UniquePtr heartbeat) {
    most_recent_echo_heartbeat = std::chrono::steady_clock::now();
    echo_heartbeat = true; // If we just received a heartbeat, then we certainly have a heartbeat!
    (void)heartbeat; // stop compiler complaining
}

void Dashboard::dvl_heartbeat_received_callback(std_msgs::msg::Empty::UniquePtr heartbeat) {
    most_recent_dvl_heartbeat = std::chrono::steady_clock::now();
    dvl_heartbeat = true; // If we just received a heartbeat, then we certainly have a heartbeat!
    (void)heartbeat; // stop compiler complaining
}


void Dashboard::joystick_heartbeat_received_callback(std_msgs::msg::Empty::UniquePtr heartbeat) {
    most_recent_joystick_heartbeat = std::chrono::steady_clock::now();
    joystick_heartbeat = true; // If we just received a heartbeat, then we certainly have a heartbeat!
    (void)heartbeat; // stop compiler complaining
}

void Dashboard::mission_manager_heartbeat_received_callback(std_msgs::msg::Empty::UniquePtr heartbeat) {
    most_recent_mission_manager_heartbeat = std::chrono::steady_clock::now();
    mission_manager_heartbeat = true; // If we just received a heartbeat, then we certainly have a heartbeat!
    (void)heartbeat; // stop compiler complaining
}

void Dashboard::pwm_cmd_callback(custom_interfaces::msg::Pwms::UniquePtr pwms) {
    pwms_cmd.pwms = pwms->pwms;
    pwms_cmd.timestamp = std::chrono::steady_clock::now();
}

void Dashboard::pwm_cli_callback(custom_interfaces::msg::Pwms::UniquePtr pwms) {
    pwms_cli.pwms = pwms->pwms;
    pwms_cli.timestamp = std::chrono::steady_clock::now();
}

void Dashboard::pwm_ctrl_callback(custom_interfaces::msg::Pwms::UniquePtr pwms) {
    pwms_ctrl.pwms = pwms->pwms;
    pwms_ctrl.timestamp = std::chrono::steady_clock::now();
}


void Dashboard::pwm_echo_callback(custom_interfaces::msg::Pwms::UniquePtr pwms) {
    pwms_echo.pwms = pwms->pwms;
    pwms_ctrl.timestamp = std::chrono::steady_clock::now();
}


void Dashboard::dvl_vr_callback(custom_interfaces::msg::VR::UniquePtr vr) {
    velocity.x = vr->velocity_data.x;
    velocity.y = vr->velocity_data.y;
    velocity.z = vr->velocity_data.z;
    velocity.timestamp = std::chrono::steady_clock::now();
}

void Dashboard::dvl_drr_callback(custom_interfaces::msg::DRR::UniquePtr drr) {
    position.x = drr->position.x;
    position.y = drr->position.y;
    position.z = drr->position.z;
    position.timestamp = std::chrono::steady_clock::now();
    orientation.x = drr->angle.x; // roll
    orientation.y = drr->angle.y; // pitch
    orientation.z = drr->angle.z; // roll
    orientation.timestamp = std::chrono::steady_clock::now();
}

void Dashboard::control_mode_callback(std_msgs::msg::UInt8::UniquePtr msg) {
    current_control_mode = msg->data;
    refresh_display();
}

void Dashboard::set_mux_mode(int mode) {
    if (mode == current_control_mode || !mux_heartbeat) {
        return;
    }
    std::shared_ptr<custom_interfaces::srv::ControlMode::Request> request = std::make_shared<custom_interfaces::srv::ControlMode::Request>();
    request->mode = mode;
    mux_client->async_send_request(request);
}

void Dashboard::reset_drr() {
    if (!dvl_heartbeat) {
        return;
    }
    std::shared_ptr<std_srvs::srv::Trigger::Request> request = std::make_shared<std_srvs::srv::Trigger::Request>();
    reset_drr_client->async_send_request(request);
}

void Dashboard::reset_gyro() {
    if (!dvl_heartbeat) {
        return;
    }
    std::shared_ptr<std_srvs::srv::Trigger::Request> request = std::make_shared<std_srvs::srv::Trigger::Request>();
    reset_gyro_client->async_send_request(request);
}

void Dashboard::toggle_ready() {
    if (!mission_manager_heartbeat) {
        return;
    }
    std::shared_ptr<std_srvs::srv::Trigger::Request> request = std::make_shared<std_srvs::srv::Trigger::Request>();
    mission_manager_client->async_send_request(request);
}


void Dashboard::ping_loop() {
    while (rclcpp::ok()) {
        usleep(10);
        auto now = std::chrono::steady_clock::now();
        if ((now - most_recent_ping_attempt) < 1s) { // Only ping a 1hz
            continue;
        }
        
        if ((now - most_recent_ping_attempt) > 5s) { // Shouldn't need this because ping generally returns an error if disconnected, but this is here as a backup
            ping_ok = false;
        }

        std::string ping_output = get_ping();
        most_recent_ping_attempt = std::chrono::steady_clock::now(); // Don't re-use from a few lines up because pinging takes time
        if (ping_output == "error") {
            ping_ok = false;
            continue;
        }

        auto rtt_location = ping_output.find("rtt"); // Location of the string "rtt", not the value of rtt
        if (rtt_location == std::string::npos || (rtt_location + 28 > ping_output.length())) { // bad message
            continue;
        }
        auto rtt_string = ping_output.substr(rtt_location + 23, 5); // extract value of rtt
        rtt = stod(rtt_string);
        most_recent_ping = most_recent_ping_attempt; // If we got here, it's a successful ping
        ping_ok = true;
    }
}

void Dashboard::work_loop() {
    tui->init_terminal();
    tui->clear_display();
    while (rclcpp::ok()) {
        bool exit = false;
        usleep(10);
        tui->process_input();
        std::string input = tui->get_current_input();
        if (input.find("\n") != std::string::npos) { // user pressed enter
            if (input.length() != 2) { // all valid input will be of form [char]\n
                tui->clear_input();
                continue;
            }
            char input_char = tolower(input[0]);
            switch (input_char) {
                case '0':
                case '1':
                case '2':
                case '3':
                    set_mux_mode((int)(input_char - '0'));
                    break;
                case 'a':
                    reset_drr();
                    break;
                case 'b':
                    reset_gyro();
                    break;
                case 'c':
                    toggle_ready();
                    break;
                case 'q':
                case 'e':
                    exit = true;
                    break;
                default:
                    break;
            }
            tui->clear_input();
        }
        if (exit) {
            break;
        }
    }

    tui->restore_terminal();
    tui->clear_display();
}

void Dashboard::refresh_display() {
    auto now = std::chrono::steady_clock::now();
    seconds_since_ping = (double)((now - most_recent_ping) / 1ms) / (double)1000;
    tui->refresh_display(19, current_control_mode,
                             thrust_interface_heartbeat,
                             mux_heartbeat,
                             cli_heartbeat,
                             ctrl_heartbeat,
                             echo_heartbeat,
                             dvl_heartbeat,
                             joystick_heartbeat,
                             mission_manager_heartbeat,
                             pwms_cmd,
                             pwms_cli,
                             pwms_ctrl,
                             pwms_echo,
                             velocity,
                             position,
                             orientation,
                             ping_ok,
                             rtt,
                             seconds_since_ping);
}
void Dashboard::clear_display() {
    tui->clear_display();
}

void Dashboard_TUI::process_input() {
    display_mutex.lock();
    int c = 0;
    while (read(STDIN_FILENO, &c, 1) != 0) {
        if ((c >= 32 && c <= 126) || c == '\n') {
            current_input.push_back(c);
            cursor_pos += 1;
        }
        if (c == 127 && cursor_pos > 0) {
            current_input.pop_back();
            cursor_pos -= 1;
        }
    }
    display_mutex.unlock();
}

void Dashboard_TUI::refresh_display(int numArgs, ...) {
    display_mutex.lock();

    va_list args;
    va_start(args, numArgs);

    tcflush(STDIN_FILENO, TCIFLUSH);
    display_tui(args);
    display_mutex.unlock();
}



void Dashboard_TUI::jump_to_column(int col_number) {
    std::string column_string = "\x1B[" + std::to_string(col_number) + "G";
    write(STDOUT_FILENO, column_string.c_str(), column_string.length());
}

void Dashboard_TUI::reset_cursor_pos() {
    write(STDOUT_FILENO, "\x1B[H", 3);
}

void Dashboard_TUI::write_header(std::string header, int col_number) {
    jump_to_column(col_number);
    write(STDOUT_FILENO, "\x1B[1m", 4); // set bold
    printf("%s\n", header.c_str());
    write(STDOUT_FILENO, "\x1B[22m", 5); // unset bold
    jump_to_column(col_number);
}

void Dashboard_TUI::write_selectable_header(std::string header, int current_mode, int active_mode, const int col_number) {
    if (active_mode == current_mode) {
        write_header("= " + header + " =", col_number);
    }
    else {
        write_header(header + "    ", col_number); // extra spaces to erase = = from when selected
    }
}

void Dashboard_TUI::display_warning_status(bool heartbeat, const int col_number) {
    jump_to_column(col_number);
    if (!heartbeat) {
        write(STDOUT_FILENO, "\x1B[5;7m", 6); // blinking, inverted
        write(STDOUT_FILENO, "\x1B[38;5;166;107m", 15); // set orange foreground, white background
        printf("== No heartbeat detected! ==\n");
        write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
    } else {
        printf("============ OK ============\n");
    }
    jump_to_column(col_number);
}

void Dashboard_TUI::display_critical_status(bool heartbeat, const int col_number) {
    jump_to_column(col_number);
    if (!heartbeat) {
        write(STDOUT_FILENO, "\x1B[5;7m", 6); // blinking, inverted
        write(STDOUT_FILENO, "\x1B[31;107m", 9); // set red foreground, white background
        printf("== No heartbeat detected! ==\n");
        write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
    } else {
        printf("============ OK ============\n");
    }
    jump_to_column(col_number);
}

void Dashboard_TUI::display_noncritical_status(bool heartbeat, const int col_number) {
    jump_to_column(col_number);
    if (!heartbeat) {
        write(STDOUT_FILENO, "\x1B[5;7m", 6); // blinking, inverted
        printf("== No heartbeat detected! ==\n");
        write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
    }
    else {
        printf("============ OK ============\n");
    }
    jump_to_column(col_number);
}

void Dashboard_TUI::display_escalatable_critical_status(int current_mode, int critical_mode, bool heartbeat, const int col_number) {
    if (current_mode == critical_mode) {
        display_critical_status(heartbeat, col_number);
    }
    else {
        display_noncritical_status(heartbeat, col_number);
    }
}

void Dashboard_TUI::display_escalatable_warning_status(int current_mode, int warning_mode, bool heartbeat, const int col_number) {
    if (current_mode == warning_mode) {
        display_warning_status(heartbeat, col_number);
    }
    else {
        display_noncritical_status(heartbeat, col_number);
    }
}


/* Note: this function returns cursor to its original position so sub-columns can be next to each other */
void Dashboard_TUI::display_pwms(std::array<int,8> pwms, const int col_number, bool fresh) {
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
        printf("| ");
        fflush(stdout);
        if (fresh) {
            write(STDOUT_FILENO, "\x1B[1;94m", 7); // set bold, blue
        }
        printf("%d\n", pwms[i]);
        if (fresh) {
            write(STDOUT_FILENO, "\x1B[39;22m", 8); // unset bold, blue
        }
    }
    write(STDOUT_FILENO, "\x1B[u", 3); // Restore cursor position
}

void Dashboard_TUI::fill_right_col(const int col_number) {
    for (int i = 0; i < 9; i++) {
        jump_to_column(col_number);
        printf("|\n");
    }
}

void Dashboard_TUI::display_all_pwms(PWM_Data pwms_cmd, PWM_Data pwms_cli, PWM_Data pwms_ctrl, PWM_Data pwms_echo) {
    printf("| - CMD - ");
    display_pwms(pwms_cmd.pwms, col_2, std::chrono::steady_clock::now() - pwms_cmd.timestamp < 0.5s);
    jump_to_column(col_2_1);
    printf("| - CLI - ");
    display_pwms(pwms_cli.pwms, col_2_1, std::chrono::steady_clock::now() - pwms_cli.timestamp < 0.5s);
    jump_to_column(col_2_2);
    printf("| - CTRL - ");
    display_pwms(pwms_ctrl.pwms, col_2_2, std::chrono::steady_clock::now() - pwms_ctrl.timestamp < 0.5s);
    jump_to_column(col_2_3);
    printf("| - ECHO - |");
    display_pwms(pwms_echo.pwms, col_2_3, std::chrono::steady_clock::now() - pwms_echo.timestamp < 0.5s);
    fill_right_col(col_2_4);
}

void Dashboard_TUI::display_connection_info(bool connection_ok, double seconds_since_ping, double ping_rtt, const int col_number) {
    jump_to_column(col_number);
    if (!connection_ok) {
        write(STDOUT_FILENO, "\x1B[5;7m", 6); // blinking, inverted
        write(STDOUT_FILENO, "\x1B[31;107m", 9); // set red foreground, white background
        printf("======== No robot connection! Check ethernet cable. ========\n");
        write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
    }
    else {
        printf("Most recent ping: rtt %.3lfms | %.1lf seconds since last ping.\n", ping_rtt, seconds_since_ping);
    }
}

void Dashboard_TUI::display_vr(const int col_number, DVL_Data velocity) {
    jump_to_column(col_number);
    std::string fresh = dvl_fresh(velocity);
    std::string clear = "\x1B[39;22m";
    printf("Velocity:    | x: %s%.5f%s | y: %s%.5f%s | z: %s%.5f%s |\n", 
        fresh.c_str(), velocity.x, clear.c_str(), 
        fresh.c_str(), velocity.y, clear.c_str(), 
        fresh.c_str(), velocity.z, clear.c_str());
}

void Dashboard_TUI::display_drr(const int col_number, DVL_Data position, DVL_Data orientation) {
    jump_to_column(col_number);
    std::string position_fresh = dvl_fresh(position);
    std::string orientation_fresh = dvl_fresh(orientation);
    std::string clear = "\x1B[39;22m";
    printf("Position:    | x: %s%.5f%s | y: %s%.5f%s | z: %s%.5f%s |\n", 
        position_fresh.c_str(), position.x, clear.c_str(), 
        position_fresh.c_str(), position.y, clear.c_str(), 
        position_fresh.c_str(), position.z, clear.c_str());
    jump_to_column(col_number);
    printf("Orientation: | x: %s%.5f%s | y: %s%.5f%s | z: %s%.5f%s |\n", 
        orientation_fresh.c_str(), orientation.x, clear.c_str(), 
        orientation_fresh.c_str(), orientation.y, clear.c_str(), 
        orientation_fresh.c_str(), orientation.z, clear.c_str());
}

std::string Dashboard_TUI::dvl_fresh(DVL_Data dvl_data) {
    if (fresh_evaluation_time - dvl_data.timestamp < 0.5s) {
        return "\x1B[1;94m"; // bold, blue
    }
    else {
        return "";
    }
}

std::string Dashboard_TUI::pwm_fresh(PWM_Data pwm_data) {
    if (fresh_evaluation_time - pwm_data.timestamp < 0.5s) {
        return "\x1B[1;94m"; // bold, blue
    }
    else {
        return "";
    }
}

void Dashboard_TUI::display_commands() {
    printf("\n===================== Commands =====================\n");
    write(STDOUT_FILENO, "\x1B[s", 3); // Save cursor position
    printf("Mux Control:\n");
    printf("[0]: Disabled\n");
    printf("[1]: CLI mode\n");
    printf("[2]: Matlab mode\n");
    printf("[3]: Echo mode\n");
    printf("\nEnter command (Q to quit) > ");
    fflush(stdout);

    write(STDOUT_FILENO, "\x1B[u", 3); // Restore cursor position
    jump_to_column(col_2);
    printf("Robot Control:\n");
    jump_to_column(col_2);
    printf("[A]: Reset DRR\n");
    jump_to_column(col_2);
    printf("[B]: Reset Gyro\n");
    jump_to_column(col_2);
    printf("[C]: Toggle Ready\n");
}

std::string Dashboard::get_ping() {
    int pipe_fds[2];
    pipe(pipe_fds); // [0] = read end, [1] = write end
    int pid = fork();
    if (pid > 0) { // Parent
        char buf[512] = {0};
        int status;
        waitpid(pid, &status, 0);
        read(pipe_fds[0], buf, 512);
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        if (status != 0) {
            return "error";
        }
        return buf;
    } else { // Child
        dup2(pipe_fds[1], STDOUT_FILENO);
        dup2(pipe_fds[1], STDERR_FILENO);
        execlp("ping", "ping", "-c 1", "propulsion.local", NULL);
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        return "error"; // should never get here
    }
}

void Dashboard_TUI::display_tui(va_list args) {
    int current_mux_mode = va_arg(args, int);
    bool thrust_interface_heartbeat = (bool)va_arg(args, int);
    bool mux_heartbeat = (bool)va_arg(args, int);
    bool cli_heartbeat = (bool)va_arg(args, int);
    bool ctrl_heartbeat = (bool)va_arg(args, int);
    bool echo_heartbeat = (bool)va_arg(args, int);
    bool dvl_heartbeat = (bool)va_arg(args, int);
    bool joystick_heartbeat = (bool)va_arg(args, int);
    bool mission_manager_heartbeat = (bool)va_arg(args, int);
    PWM_Data pwms_cmd = va_arg(args, PWM_Data);
    PWM_Data pwms_cli = va_arg(args, PWM_Data);
    PWM_Data pwms_ctrl = va_arg(args, PWM_Data);
    PWM_Data pwms_echo = va_arg(args, PWM_Data);
    DVL_Data velocity = va_arg(args, DVL_Data);
    DVL_Data position = va_arg(args, DVL_Data);
    DVL_Data orientation = va_arg(args, DVL_Data);
    bool ping_ok = (bool)va_arg(args, int);
    double ping_rtt = va_arg(args, double);
    double seconds_since_ping = va_arg(args, double);
    va_end(args);
    
    fresh_evaluation_time = std::chrono::steady_clock::now();

    write(STDOUT_FILENO, "\x1B[?25l", 6); // invisible cursor
    reset_cursor_pos();

    write_header("thrust_interface", col_1);
    display_critical_status(thrust_interface_heartbeat, col_1);
    printf("\n");

    write_header("soft_mux", col_1);
    display_critical_status(mux_heartbeat, col_1);
    printf("\n");

    write_selectable_header("cli", current_mux_mode, 1, col_1);
    display_escalatable_critical_status(current_mux_mode, 1, cli_heartbeat, col_1);
    printf("\n");

    write_selectable_header("ctrl", current_mux_mode, 2, col_1);
    display_escalatable_critical_status(current_mux_mode, 2, ctrl_heartbeat, col_1);
    printf("\n");

    write_selectable_header("echo", current_mux_mode, 3, col_1);
    display_escalatable_critical_status(current_mux_mode, 3, echo_heartbeat, col_1);
    printf("\n");

    write_header("dvl", col_1);
    display_critical_status(dvl_heartbeat, col_1);
    display_vr(col_1, velocity);
    display_drr(col_1, position, orientation);
    printf("\n");

    write_header("Robot Connection Status", col_1);
    display_connection_info(ping_ok, seconds_since_ping, ping_rtt, col_1);

    printf("\n");
    printf("Systems in flashing red are critical and should be fixed immediately.\n");
    printf("Systems in flashing orange might be critical and should be fixed if needed.\n");
    printf("Systems in flashing white are not connected, but are noncritical and can probably be ignored.\n");
    printf("The current control mode is indicated by whether the mode is highlighted by = [mode] =.\n");
    printf("Fresh PWM and DVL data is shown bolded in blue. After 0.5s it becomes stale and returns to normal.\n ");

    display_commands();  
    
    reset_cursor_pos();

    write_header("PWMs", col_2);
    display_all_pwms(pwms_cmd, pwms_cli, pwms_ctrl, pwms_echo);
    printf("\n");

    write_header("Joystick", col_2);
    display_escalatable_critical_status(current_mux_mode, 2, joystick_heartbeat, col_2);
    printf("\n");

    write_header("mission_manager", col_2);
    display_escalatable_warning_status(current_mux_mode, 2, mission_manager_heartbeat, col_2);

    write(STDOUT_FILENO, "\x1B[38;29H", 8); // jumpt to prompt (line/column)
    write(STDOUT_FILENO, "\x1B[?25h", 6); // visible cursor
    printf("%s", current_input.c_str());
    write(STDOUT_FILENO, "\x1B[0K", 4); // erase until end of line (removes backspaced characters)

    fflush(stdout);
}

// TODO: Add voltage, ability to reset dvl drr and gyro, mission manager heartbeat

int main(int argc, char* argv[]) {    
    rclcpp::init(argc, argv);
    std::unique_ptr<TUI_Interface> tui = std::make_unique<Dashboard_TUI>();
    auto dashboard = std::make_shared<Dashboard>(std::move(tui));
    
    std::thread ros_thread([&]() { // Needs to be seperate thread so that work loop can run
        rclcpp::spin(dashboard);
    });
    std::thread ping_thread([&]() { // Needs to be seperate thread so that ping delays don't freeze program
        dashboard->ping_loop();
    });

    dashboard->work_loop();

    rclcpp::shutdown();
    ros_thread.join();
    ping_thread.join();
    
    return 0;
}
