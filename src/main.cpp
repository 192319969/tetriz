#include "define.h"
#include "terminal.h"
#include "utils.h"
#include "draw.h"
#include "control.h"
#include "game.h"
#include "tetromino.h"
#include "window.h"

void init(){
#ifdef _WIN32
    system("chcp 65001");
#endif
    tc::hide_cursor();
    tc::clear_screen();
    ui::show_windows();
    ui::show_help();
    gm::init();
    gm::start_listener();
    setbuf(stdout,nullptr);
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

void exit(){
    tc::show_cursor();
    ui::show_exit();
    tc::reset_color();
}

int main() {

    init();
    loop();
    exit();

    return 0;
}