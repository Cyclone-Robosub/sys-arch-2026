#include "mux_controller.hpp"

using namespace std::chrono_literals;

Mux_Controller::Mux_Controller() : Node("mux_controller"), current_control_mode(0) {
    current_control_mode_subscriber = this->create_subscription<std_msgs::msg::UInt8>("current_mode", 10, 
        std::bind(&Mux_Controller::control_mode_callback, this, std::placeholders::_1));
    heartbeat_subscription = this->create_subscription<std_msgs::msg::Bool>("mux_heartbeat", 10, 
        std::bind(&Mux_Controller::mux_heartbeat_received_callback, this, std::placeholders::_1));
    
    heartbeat_timer = this->create_wall_timer(500ms, 
            std::bind(&Mux_Controller::heartbeat_check_callback, this)); // heartbeat timer

    client = this->create_client<custom_interfaces::srv::ControlMode>("control_mode");
    force_pub = this->create_client<std_srvs::srv::SetBool>("force_pub");
}

void Mux_Controller::get_mux_mode_now() {
    std::shared_ptr<std_srvs::srv::SetBool::Request> request = std::make_shared<std_srvs::srv::SetBool::Request>();
    request->data = true;
    force_pub->async_send_request(request);
}

void Mux_Controller::set_mux_mode(int mode) {
    if (mode == current_control_mode || no_heartbeat) {
        state_change_mutex.lock();
        state_changed = true;
        state_change_mutex.unlock();
        return;
    }
    std::shared_ptr<custom_interfaces::srv::ControlMode::Request> request = std::make_shared<custom_interfaces::srv::ControlMode::Request>();
    request->mode = mode;
    client->async_send_request(request);
}

void Mux_Controller::mux_heartbeat_received_callback(std_msgs::msg::Bool::UniquePtr heartbeat) {
    most_recent_heartbeat = std::chrono::steady_clock::now();
    if (no_heartbeat) {
        no_heartbeat = false; // If we just received a heartbeat, then we certainly have a heartbeat!
        get_mux_mode_now();
        state_change_mutex.lock();
        state_changed = true;
        state_change_mutex.unlock();
    }
    (void)heartbeat; // stop compiler complaining
}

void Mux_Controller::heartbeat_check_callback() {
    auto current_time = std::chrono::steady_clock::now();
    if (current_time - most_recent_heartbeat > 1s) {
        if (!no_heartbeat) {
            no_heartbeat = true;
            state_change_mutex.lock();
            state_changed = true;
            state_change_mutex.unlock();
        }
    }
    else {
        no_heartbeat = false;
    }
}

void Mux_Controller::control_mode_callback(std_msgs::msg::UInt8::UniquePtr msg) {
    current_control_mode = msg->data;
    state_change_mutex.lock();
    state_changed = true;
    state_change_mutex.unlock();
}

int Mux_Controller::get_current_control_mode() {
    return current_control_mode;
}

bool Mux_Controller::is_no_heartbeat() {
    return no_heartbeat;
}

bool Mux_Controller::is_new_state() {
    bool retval = state_changed;
    state_changed = false;
    return retval;
}

void Mux_Controller_TUI::display_tui() {
    if (mux_controller->is_no_heartbeat()) {
        write(STDOUT_FILENO, "\x1B[5m", 4); // set blinking
        write(STDOUT_FILENO, "\x1B[1;7m", 6); // set bold, inverted
        printf("====== No heartbeat detected from Mux! ======\n\n");
        write(STDOUT_FILENO, "\x1B[0m", 4); // reset style
    }
    else {
        printf("Current mode is: ");
        switch (mux_controller->get_current_control_mode()) {
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

void Mux_Controller_TUI::work_loop() {
    char mode = 0;
    int string_index = 0;
    refresh_display();

    while (rclcpp::ok()) {
        process_input();
        if (mux_controller->is_new_state()) {
            refresh_display();
        }
        display_mutex.lock();
        mode = current_input[0];
        mode = tolower(mode);

        if (current_input.size() < 2) {
            printf("Invalid command. Try again: ");
            fflush(stdout);
            display_mutex.unlock();
            continue; 
        }

        string_index = 1;
        if (mode == 'e' || mode == 'q') {
            display_mutex.unlock();
            break;
        }
        if (current_input[string_index] != '\n' || (mode != '0' && mode != '1' && mode != '2' && mode != '3')) {
            printf("Invalid command. Try again: ");
            fflush(stdout);
            while (current_input[string_index] != '\n') {
                string_index++;
            }
            display_mutex.unlock();
            continue;
        }
        display_mutex.unlock();
        mux_controller->set_mux_mode((int)(mode - '0'));
    }
}

void Mux_Controller_TUI::run_tui() {
    std::thread ros_thread([&]() { // Needs to be seperate thread so that input loop can run
        rclcpp::spin(mux_controller);
    });

    init_terminal();
    work_loop();
    restore_terminal();

    rclcpp::shutdown();
    ros_thread.join();

    clear_display();
}

Mux_Controller_TUI::Mux_Controller_TUI(std::shared_ptr<Mux_Controller> mux_controller) : TUI_Interface(), mux_controller(mux_controller) {}

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    auto mux_controller = std::make_shared<Mux_Controller>();
    auto mux_controller_tui = Mux_Controller_TUI(mux_controller);
    mux_controller_tui.run_tui();
    
    return 0;
}
