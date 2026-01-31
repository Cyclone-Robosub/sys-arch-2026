#include <fd-interface.hpp>

Path_FD::Path_FD(std::string path) : 
    FD_Interface(),
    path(path) 
     {
    fd = open_serial();
}

int Path_FD::get_fd() {
    return fd;
}

void Path_FD::attempt_reconnect() {
    fd = open_serial();
}

void Path_FD::close_fd() {
    if (fd >= 0) {
        close(fd);
    }
}

int Path_FD::open_serial() {
    struct termios tty;
    speed_t baud = 115200;
    int fd;
    
    if ((fd = open(path.c_str(), O_RDWR | O_NOCTTY | O_SYNC)) == -1) {
        return -1;
    }
    
    fcntl(fd, F_SETFL, O_RDWR);
    
    // Get and modify current options:
    cfsetospeed(&tty, baud);
    cfsetispeed(&tty, baud);
    
    // Configure 8N1, no flow control
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8 bits
    tty.c_cflag &= ~PARENB; // no parity
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CRTSCTS; // no hardware flow control
    tty.c_cflag |= CLOCAL | CREAD; // enable receiver

    tty.c_lflag = 0; // non-canonical mode
    tty.c_oflag = 0; // no remapping, no delays
    tty.c_iflag = 0; // no special handling

    tty.c_cc[VMIN] = 0;  // non-blocking read
    tty.c_cc[VTIME] = 10; // 1 second timeout (VTIME is in deciseconds)
    
    tcsetattr(fd, TCSANOW, &tty);
    
    return fd;
}

Path_FD::~Path_FD() {
    close_fd();
}

Direct_FD::Direct_FD(int fd) :
    FD_Interface()
     {
        this->fd = fd;
}

int Direct_FD::get_fd() {
    return fd;
}
void Direct_FD::attempt_reconnect() {
    return;
}
void Direct_FD::close_fd() {
    if (fd >= 0) {
        close(fd);
    }
}

Direct_FD::~Direct_FD() {
    close_fd();
}