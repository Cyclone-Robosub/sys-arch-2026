#include "tui.hpp"

using namespace std::chrono_literals;

Dashboard::Dashboard(std::unique_ptr<TUI_Interface> tui) : Node("tui"), tui(std::move(tui)) {
    current_control_mode_subscriber = this->create_subscription<std_msgs::msg::UInt8>("current_mode", 10, 
        std::bind(&Dashboard::control_mode_callback, this, std::placeholders::_1));
    heartbeat_subscription = this->create_subscription<std_msgs::msg::Empty>("mux_heartbeat", 10, 
        std::bind(&Dashboard::mux_heartbeat_received_callback, this, std::placeholders::_1));
    
    heartbeat_timer = this->create_wall_timer(500ms, 
            std::bind(&Dashboard::heartbeat_check_callback, this)); // heartbeat timer    

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

void Dashboard_TUI::display_tui(va_list args) {
    bool no_heartbeat = (bool)va_arg(args, int);
    int current_control_mode = va_arg(args, int);
    va_end(args);
    if (no_heartbeat) {
        write(STDOUT_FILENO, "\x1B[5m", 4); // set blinking
        write(STDOUT_FILENO, "\x1B[1;7m", 6); // set bold, inverted
        printf("====== No heartbeat detected from Mux! ======\n\n");
        write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
    }
    else {
        printf("Current mode is: ");
        switch (current_control_mode) {
            case 0:
                printf("disabled");
                break;
            case 1:
                printf("cli");
                break;
            case 2:
                printf("matlab (ctrl)");
                break;
            case 3:
                printf("echo (playback)");
                break;
        }
        printf("\n\n");
    }
    printf("Enter the control mode you'd like to switch to.\n");
    printf("[0]: Disabled\n");
    printf("[1]: CLI mode\n");
    printf("[2]: Matlab mode\n");
    printf("[3]: Echo mode\n");
    printf("[E]: Exit\n");
    printf("Mode: ");
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
