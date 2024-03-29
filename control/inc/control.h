#pragma once
#include <string>

namespace gm
{
    extern char command;
#ifdef __linux__
    char getch();
#endif
    void key_event();
    void start_listener();

    std::string get_command();

    //键盘事件
    void command_quit();
    void command_rotate_R();
    void command_rotate_L();
    void command_rotate_2();
    void command_left();
    void command_right();
    void command_down();
    void command_drop();
    void command_hold();
    void command_help();
    void command_reset();

}