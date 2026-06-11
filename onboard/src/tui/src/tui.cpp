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

    client = this->create_client<custom_interfaces::srv::ControlMode>("control_mode");
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

void Dashboard::pwm_cmd_callback(custom_interfaces::msg::Pwms::UniquePtr pwms) {
    pwms_cmd = pwms->pwms;
}

void Dashboard::pwm_cli_callback(custom_interfaces::msg::Pwms::UniquePtr pwms) {
    pwms_cli = pwms->pwms;
}

void Dashboard::pwm_ctrl_callback(custom_interfaces::msg::Pwms::UniquePtr pwms) {
    pwms_ctrl = pwms->pwms;
}


void Dashboard::pwm_echo_callback(custom_interfaces::msg::Pwms::UniquePtr pwms) {
    pwms_echo = pwms->pwms;
}


void Dashboard::dvl_vr_callback(custom_interfaces::msg::VR::UniquePtr vr) {
    vx = vr->velocity_data.x;
    vy = vr->velocity_data.y;
    vz = vr->velocity_data.z;
}

void Dashboard::dvl_drr_callback(custom_interfaces::msg::DRR::UniquePtr drr) {
    x = drr->position.x;
    y = drr->position.y;
    z = drr->position.z;
    roll = drr->angle.x;
    pitch = drr->angle.y;
    yaw = drr->angle.z;
}

void Dashboard::control_mode_callback(std_msgs::msg::UInt8::UniquePtr msg) {
    current_control_mode = msg->data;
    refresh_display();
}

void Dashboard::work_loop() {
    tui->init_terminal();
    tui->clear_display();

    while (rclcpp::ok()) {
        usleep(10);
        if ((std::chrono::steady_clock::now() - most_recent_ping_attempt) < 1s) {
            continue;
        }
        
        std::string ping_output = get_ping();
        most_recent_ping_attempt = std::chrono::steady_clock::now();
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
        most_recent_ping = most_recent_ping_attempt;
        ping_ok = true;
    }

    tui->restore_terminal();
    tui->clear_display();
}

void Dashboard::refresh_display() {
    seconds_since_ping = (double)((std::chrono::steady_clock::now() - most_recent_ping) / 1ms) / (double)1000;
    tui->refresh_display(24, current_control_mode,
                             thrust_interface_heartbeat,
                             mux_heartbeat,
                             cli_heartbeat,
                             ctrl_heartbeat,
                             echo_heartbeat,
                             dvl_heartbeat,
                             joystick_heartbeat,
                             pwms_cmd.data(),
                             pwms_cli.data(),
                             pwms_ctrl.data(),
                             pwms_echo.data(),
                             vx,
                             vy,
                             vz,
                             x,
                             y,
                             z,
                             roll,
                             pitch,
                             yaw,
                             ping_ok,
                             rtt,
                             seconds_since_ping);
}
void Dashboard::clear_display() {
    tui->clear_display();
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

void Dashboard_TUI::write_selectable_header(std::string header, int current_mode, int active_mode, int col_number) {
    if (active_mode == current_mode) {
        write_header("= " + header + " =", col_number);
    }
    else {
        write_header(header + "    ", col_number); // extra spaces to erase = = from when selected
    }
}

void Dashboard_TUI::display_critical_status(bool heartbeat, int col_number) {
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

void Dashboard_TUI::display_noncritical_status(bool heartbeat, int col_number) {
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

void Dashboard_TUI::display_escalatable_status(int current_mode, int critical_mode, bool heartbeat, int col_number) {
    if (current_mode == critical_mode) {
        display_critical_status(heartbeat, col_number);
    }
    else {
        display_noncritical_status(heartbeat, col_number);
    }
}

/* Note: this function returns cursor to its original position so sub-columns can be next to each other*/
void Dashboard_TUI::display_pwms(int* pwms, int col_number) {
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

void Dashboard_TUI::fill_right_col(int col_number) {
    for (int i = 0; i < 9; i++) {
        jump_to_column(col_number);
        printf("|\n");
    }
}

void Dashboard_TUI::display_all_pwms(int* pwms_cmd, int* pwms_cli, int* pwms_ctrl, int* pwms_echo, int main_col, int sub_col_1, int sub_col_2, int sub_col_3) {
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

void Dashboard_TUI::display_connection_info(bool connection_ok, double seconds_since_ping, double ping_rtt, int col_number) {
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

void Dashboard_TUI::display_vr(int col_number, double vx, double vy, double vz) {
    jump_to_column(col_number);
    printf("Velocity:    | x: %.5f | y: %.5f | z: %.5f |\n", vx, vy, vz);
}

void Dashboard_TUI::display_drr(int col_number, double x, double y, double z, double roll, double pitch, double yaw) {
    jump_to_column(col_number);
    printf("Position:    | x: %.5f | y: %.5f | z: %.5f |\n", x, y, z);
    jump_to_column(col_number);
    printf("Orientation: | x: %.5f | y: %.5f | z: %.5f |\n", roll, pitch, yaw);
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
    int* pwms_cmd = va_arg(args, int*);
    int* pwms_cli = va_arg(args, int*);
    int* pwms_ctrl = va_arg(args, int*);
    int* pwms_echo = va_arg(args, int*);
    double vx = va_arg(args, double);
    double vy = va_arg(args, double);
    double vz = va_arg(args, double);
    double x = va_arg(args, double);
    double y = va_arg(args, double);
    double z = va_arg(args, double);
    double roll = va_arg(args, double);
    double pitch = va_arg(args, double);
    double yaw = va_arg(args, double);
    bool ping_ok = (bool)va_arg(args, int);
    double ping_rtt = va_arg(args, double);
    double seconds_since_ping = va_arg(args, double);
    va_end(args);

    int first_col = 0;
    int second_col = 35;

    reset_cursor_pos();

    write_header("thrust_interface", first_col);
    display_critical_status(thrust_interface_heartbeat, first_col);
    printf("\n");

    write_header("soft_mux", first_col);
    display_critical_status(mux_heartbeat, first_col);
    printf("\n");

    write_selectable_header("cli", current_mux_mode, 1, first_col);
    display_escalatable_status(current_mux_mode, 1, cli_heartbeat, first_col);
    printf("\n");

    write_selectable_header("ctrl", current_mux_mode, 2, first_col);
    display_escalatable_status(current_mux_mode, 2, ctrl_heartbeat, first_col);
    printf("\n");

    write_selectable_header("echo", current_mux_mode, 3, first_col);
    display_escalatable_status(current_mux_mode, 3, echo_heartbeat, first_col);
    printf("\n");

    write_header("dvl", first_col);
    display_critical_status(dvl_heartbeat, first_col);
    display_vr(first_col, vx, vy, vz);
    display_drr(first_col, x, y, z, roll, pitch, yaw);
    printf("\n");

    write_header("Robot Connection Status", first_col);
    display_connection_info(ping_ok, seconds_since_ping, ping_rtt, first_col);

    printf("\n");
    printf("Systems in flashing red are critical and and should be fixed immediately.\n");
    printf("Systems in flashing white are not connected, but are noncritical and can probably be ignored.\n");
    printf("The current control mode is indicated by whether the mode is highlighted by = [mode] =.\n");
    
    reset_cursor_pos();

    write_header("pwms", second_col);
    display_all_pwms(pwms_cmd, pwms_cli, pwms_ctrl, pwms_echo, second_col, 45, 55, 66);
    printf("\n");

    printf("\n");
    write_header("Joystick", second_col);
    display_escalatable_status(current_mux_mode, 2, joystick_heartbeat, second_col);
    printf("\n");

    reset_cursor_pos();

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
