#include "control.h"
#include "define.h"
#include "game.h"

namespace gm{

    char command;

    std::map<char,std::function<void()>> command_fuc{
        {KEY_Q,command_quit},
        {KEY_W,command_rotate_R},
        {KEY_Z,command_rotate_L},
        {KEY_X,command_rotate_2},
        {KEY_A,command_left},
        {KEY_D,command_right},
        {KEY_S,command_down},
        {KEY_C,command_hold},
        {KEY_R,command_reset},
        {KEY_SPACE,command_drop}
    };

    char getch()
    {
        char c;
        struct termios old,cur;
        tcgetattr(0,&cur);
        old=cur;
        cfmakeraw(&cur);
        tcsetattr(0,0,&cur);
        c=getchar();
        tcsetattr(0,0,&old);
        return c;
    }

    void key_event()
    {
        while (running)
        {
            //windows下使用_getch(),可以不用回车
            command=getch();
            if(command_fuc.find(command)!=command_fuc.end())
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
    void command_drop(){
        drop();
    }
    void command_hold(){
        hold();
    }
    void command_reset(){
        reset();
    }

}