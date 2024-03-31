#pragma once

namespace gm
{
    extern char command;
#ifdef __linux__
    char getch();
#endif
    void key_event();
    void start_listener();

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
    //===================P2===================
    void command_rotate_R2();
    void command_rotate_L2();
    void command_rotate_22();
    void command_left2();
    void command_right2();
    void command_down2();
    void command_drop2();
    void command_hold2();
    void command_help2();
    void command_reset2();
}