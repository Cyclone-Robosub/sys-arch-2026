#include "fd_interface.hpp"

Path_FD::Path_FD(std::string path) : 
    FD_Interface(),
    path(path) 
     {}

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
