#include <string>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <mutex>

#ifndef TUI_INTERFACE
#define TUI_INTERFACE

/*
 * For ANSI escape sequences, see: https://gist.github.com/ConnerWill/d4b6c776b509add763e17f9f113fd25b
*/

class TUI_Interface {
protected:
    std::mutex display_mutex;
    std::string current_input;
    int cursor_pos = 0;
    int num_read = 0;
    struct termios orig_termios;
public:
    explicit TUI_Interface() {};
    virtual void display_tui() = 0;
    virtual void clear_display();
    virtual void refresh_display();
    virtual void insert_into_input(char c);
    virtual void backspace();
    virtual void delete_or_direction();
    virtual void process_input();
    virtual void init_terminal();
    virtual void restore_terminal();

};

#endif // TUI_INTERFACE