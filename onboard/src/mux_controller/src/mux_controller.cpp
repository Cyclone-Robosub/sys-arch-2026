#include "mux_controller.hpp"

Mux_Controller::Mux_Controller() : Node("mux_controller") {
    current_control_mode_subscriber = this->create_subscription<std_msgs::msg::Bool>(
        "current_mode", 10, 
        std::bind(&Mux_Controller::control_mode_callback, this, std::placeholders::_1));
        std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("SoftMux");
        client = node->create_client<std_srvs::srv::SetBool>("control_mode");
        refresh_display();
}

void Mux_Controller::set_mux_mode(bool mode) {
    // std::shared_ptr<std_srvs::srv::SetBool::Request> request = std::make_shared<std_srvs::srv::SetBool::Request>();
    // request->data = mode;
    // client->async_send_request(request);
    current_control_mode = mode;
    refresh_display();
}

void Mux_Controller::control_mode_callback(std_msgs::msg::Bool::UniquePtr msg) {
    current_control_mode = msg->data;
    refresh_display();
}

void Mux_Controller::refresh_display() {
    printf("\e[1;1H\e[2J"); // clear display
    printf("Current mode is: %s\n\n", current_control_mode ? "matlab" : "cli" );
    printf("Enter the control mode you'd like to switch to.\n");
    printf("[0]: CLI mode\n");
    printf("[1]: Matlab mode\n");
    printf("[E]: Exit\n");
    printf("Mode: ");
}

int main(int argc, char* argv[]) {
    
    
    rclcpp::init(argc, argv);
    auto mux_controller = std::make_shared<Mux_Controller>();
    rclcpp::spin_some(mux_controller);
    
    char mode = 0;
    char should_be_newline = 0;

    while (true) {
        scanf("%c", &mode);
        scanf("%c", &should_be_newline);
        if (mode == 'E') {
            break;
        }
        if (mode != '0' && mode != '1') {
            printf("Invalid command. Try again.");
            // printf("\e[1;1H\e[2J"); // clear display
            continue;
        }
        
        mux_controller->set_mux_mode((bool)(mode - '0'));
    }

    rclcpp::shutdown();

    printf("\e[1;1H\e[2J"); // clear display
    
    return 0;
}