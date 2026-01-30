#include <string>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

class FD_Interface {
protected:
    int fd;
public:
    explicit FD_Interface() {};
    virtual int get_fd() = 0;
    virtual void attempt_reconnect() = 0;
    virtual void close_fd() = 0;
};

class Path_FD : public FD_Interface {
protected:
    std::string path;
    virtual int open_serial() = 0;
public:
    Path_FD(std::string path);
    int get_fd() override;
    void attempt_reconnect() override;
    void close_fd() override;
    ~Path_FD();
};

class Direct_FD : public FD_Interface {
public:
    Direct_FD(int fd);
    int get_fd() override;
    void attempt_reconnect() override;
    void close_fd() override;
    ~Direct_FD();
};
