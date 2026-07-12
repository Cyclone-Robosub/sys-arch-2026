#include "pico_go_switch.hpp"

using namespace std::chrono_literals;
using namespace rclcpp;

Pico_Go_Switch::Pico_Go_Switch(std::unique_ptr<FD_Interface> pico_fd) :
    Node("pico_go_switch"), 
    pico_fd(std::move(pico_fd)) {
    heartbeat_publisher = this->create_publisher<std_msgs::msg::Bool>("go_signal", 10);
    go_signal_check_timer = this->create_wall_timer(50ms, 
            std::bind(&Pico_Go_Switch::check_for_go_signal, this));
}
    
void Pico_Go_Switch::check_for_go_signal() {
    const size_t buffer_length = 128;
    char buffer[buffer_length] = {0};
    
    ssize_t bytes_written = read(pico_fd->get_read_fd(), buffer, buffer_length);
    
    if (bytes_written != 0) {
        std::string pico_message = std::string(buffer);
        if (pico_message == "True") {
            publish_go_signal();
        }
    }
}

void Pico_Go_Switch::publish_go_signal() {
    std_msgs::msg::Bool msg;
    msg.data = true;
    heartbeat_publisher->publish(msg);
}

Pico_FD::Pico_FD(std::string path) : Path_FD(path) {
    fd = open_file();
}

int Pico_FD::open_file() {
    struct termios options;
    speed_t baud = 115200;
    int status, fd;
    
    if ((fd = open(path.c_str(), O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) == -1) {
        return -1;
    }
    
    fcntl(fd, F_SETFL, O_RDWR);
    
    // Get and modify current options:
    tcgetattr(fd, &options);
    cfmakeraw(&options);
    cfsetispeed(&options, baud);
    cfsetospeed(&options, baud);
    
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    
    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 1;  // 1/10 (1 decisecond)
    
    tcsetattr(fd, TCSANOW, &options);
    
    ioctl(fd, TIOCMGET, &status);
    status |= TIOCM_DTR;
    status |= TIOCM_RTS;
    ioctl(fd, TIOCMSET, &status);
    
    usleep(100000);  // 100ms
    
    return fd;
}

#ifndef ENABLE_TESTING

int main(int argc, char* argv[]) {
    std::unique_ptr<FD_Interface> fd = std::make_unique<Pico_FD>("/dev/serial/by-id/usb-MicroPython_Board_in_FS_mode_e6654854576e6725-if00");
    rclcpp::init(argc, argv);
    auto pico_go_switch = std::make_shared<Pico_Go_Switch>(std::move(fd));
    rclcpp::spin(pico_go_switch);
    
    rclcpp::shutdown();
    
    return 0;
}
#endif

