#include "define.h"
#include "terminal.h"
#include "utils.h"
#include "draw.h"
#include "control.h"
#include "game.h"
#include "tetromino.h"
#include "window.h"

void init(){
    tc::hide_cursor();
    tc::clear_screen();
    ui::show_windows();
    ui::show_help();
    gm::init();
    gm::start_listener();
    // setbuf(stdout,nullptr);
}

void init2(){
    tc::hide_cursor();
    tc::clear_screen();
    ui::show_windows2();
    ui::show_help2();
    gm::init2();
    gm::start_listener();
    // setbuf(stdout,nullptr);
}

void loop(){
    while (gm::running)
    {   
        gm::process();

        ui::show_info();
        ui::show_game();
        
        std::this_thread::sleep_for(15.625ms);//s ms us ns
    }
}

void loop2(){
    while (gm::running||gm::running2)
    {   
        gm::process();
        gm::process2();

        ui::show_info();
        ui::show_game();

        tc::reset_color();    
        ui::show_info2();
        ui::show_game2();
        
        std::this_thread::sleep_for(15.625ms);//s ms us ns
    }
}

void exit(){
    tc::show_cursor();
    ui::show_exit();
    tc::reset_color();
}

int main() {

    init2();
    loop2();
    exit();

    return 0;
}