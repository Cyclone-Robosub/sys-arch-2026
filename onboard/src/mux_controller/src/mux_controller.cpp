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
        refresh_display();
    }
    (void)heartbeat; // stop compiler complaining
}

void Mux_Controller::heartbeat_check_callback() {
    auto current_time = std::chrono::steady_clock::now();
    if (current_time - most_recent_heartbeat > 1s) {
        no_heartbeat = true;
        refresh_display();
    }
    else {
        no_heartbeat = false;
    }
}

bool Mux_Controller::is_heartbeat() {
    return !no_heartbeat;
}


void Mux_Controller::control_mode_callback(std_msgs::msg::Bool::UniquePtr msg) {
    current_control_mode = msg->data;
    refresh_display();
}

void Mux_Controller::clear_display() {
    printf("\e[1;1H\e[2J");
}

void Mux_Controller::refresh_display() {
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

int main(int argc, char* argv[]) {
    
    
    rclcpp::init(argc, argv);
    auto mux_controller = std::make_shared<Mux_Controller>();
    
    std::thread ros_thread([&]() { // Needs to be seperate thread so that input loop can run
        rclcpp::spin(mux_controller);
    });

    while (!mux_controller->is_heartbeat() && rclcpp::ok()) {
        // wait until we get a heartbeat
    }
    mux_controller->get_mux_mode_now();

    char mode = 0;
    char should_be_newline = 0;

    while (rclcpp::ok()) {
        scanf("%c", &mode);
        scanf("%c", &should_be_newline);
        mode = tolower(mode);
        if (mode == 'e' || mode == 'q') {
            break;
        }
        if (should_be_newline != '\n' || (mode != '0' && mode != '1')) {
            printf("Invalid command. Try again: ");
            while (should_be_newline != '\n') {
                scanf("%c", &should_be_newline);
            }
            continue;
        }
        
        mux_controller->set_mux_mode((bool)(mode - '0'));
    }

    rclcpp::shutdown();
    ros_thread.join();

    Mux_Controller::clear_display();
    
    return 0;
}