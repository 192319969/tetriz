#ifndef _TERMINAL_H
#define _TERMINAL_H
#include "define.h"
namespace tc{//terminal control
    void move_to(int row, int col, std::ostream &os=std::cout);
    void set_fore_color(int id, std::ostream &os=std::cout);
    void set_back_color(int id, std::ostream &os=std::cout);
    void clear_screen(std::ostream &os=std::cout);
    void reset_color(std::ostream &os=std::cout);
    void hide_cursor(std::ostream &os=std::cout);
    void show_cursor(std::ostream &os=std::cout);
}
#endif // _TERMINAL_H
