#include "control.h"
#include "define.h"
#include "game.h"

namespace gm
{

    char command;

    std::map<char, std::function<void()>> command_fuc{
        {KEY_Q, command_quit},
        {KEY_W, command_rotate_R},
        {KEY_Z, command_rotate_L},
        {KEY_X, command_rotate_2},
        {KEY_A, command_left},
        {KEY_D, command_right},
        {KEY_S, command_down},
        {KEY_C, command_hold},
        {KEY_H, command_help},
        {KEY_R, command_reset},
        {KEY_SPACE, command_drop},        
        //============================P2=====================================
        {KEY_UP,    command_rotate_R2},
        {KEY_4,     command_rotate_L2},
        {KEY_6,     command_rotate_22},
        {KEY_LEFT,  command_left2},
        {KEY_RIGHT, command_right2},
        {KEY_DOWN,  command_down2},
        {KEY_0,     command_drop2},
        {KEY_7,     command_hold2},
        {KEY_8,     command_help2},
        {KEY_9,     command_reset2}
    };

#ifdef __linux__
    char getch()
    {
        char c;
        struct termios old, cur;
        tcgetattr(0, &cur);
        old = cur;
        cfmakeraw(&cur);
        tcsetattr(0, 0, &cur);
        c = getchar();
        tcsetattr(0, 0, &old);
        return c;
    }
#endif

    void key_event()
    {
        while (running)
        {
            // windows下使用_getch(),可以不用回车
            command = getch();
            if (command_fuc.find(command) != command_fuc.end())
                command_fuc[command]();
        }
    }

    void start_listener()
    {
        std::thread t(key_event);
        t.detach();
    }
    void command_quit()
    {
        quit();
    }
    void command_rotate_R()
    {
        rotate(1);
    }
    void command_rotate_L()
    {
        rotate(2);
    }
    void command_rotate_2()
    {
        rotate(3);
    }
    void command_left()
    {
        left();
    }
    void command_right()
    {
        right();
    }
    void command_down()
    {
        down();
    }
    void command_drop()
    {
        drop();
    }
    void command_hold()
    {
        hold();
    }
    void command_help()
    {
        help();
    }
    void command_reset()
    {
        reset();
    }

    //============================P2=====================================
    void command_rotate_R2()
    {
        rotate2(1);
    }
    void command_rotate_L2()
    {
        rotate2(2);
    }
    void command_rotate_22()
    {
        rotate2(3);
    }
    void command_left2()
    {
        left2();
    }
    void command_right2()
    {
        right2();
    }
    void command_down2()
    {
        down2();
    }
    void command_drop2()
    {
        drop2();
    }
    void command_hold2()
    {
        hold2();
    }
    void command_help2()
    {
        help2();
    }
    void command_reset2()
    {
        reset2();
    }
}