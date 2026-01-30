#include "fd_interface.hpp"

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
