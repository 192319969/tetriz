#include "window.h"
#include "draw.h"
#include "game.h"
#include "terminal.h"
#include "utils.h"

namespace ui
{
    void show_windows(){
        dw::window(1, 1, 9, 6, "Hold");
        dw::window(1, 10, 12, 22, "Tetriz");
        dw::window(7, 1, 9, 16, "Status");
        dw::window(19, 22, 8, 4, "Info");
        dw::window(1, 22, 8, 18, "Next");
    }
    void show_info()
    {
        tc::reset_color();
        //show fps
        tc::move_to(10, 4);
        std::cout << "FPS: " << ut::fps();
        tc::move_to(12, 4);
        std::cout << "Level: " << gm::level;
        tc::move_to(13, 4);
        std::cout << "Score: " << gm::score;
        tc::move_to(14, 4);
        std::cout << "Lines: " << gm::lines;

        if(gm::ending){
            dw::window(9, 12, 10, 3, "");
            tc::move_to(10, ut::block2col(14));
            tc::set_fore_color((int)Color::Red);
            std::cout << " Game Over!";
        }
    }
    void show_game()
    {
        dw::frame(gm::frame, 2, 11);
        dw::next(gm::next, 2, 23);
        dw::hold(gm::hold_piece,2,2);
        std::cout << std::flush;
    }
    void show_exit()
    {
        tc::clear_screen();
        tc::move_to(1, 1);
        tc::set_fore_color(9);
        std::cout << "Thank you for playing tetriz!" << std::endl;
    }
    void show_help()
    {
        tc::reset_color();
        tc::move_to(21,ut::block2col(24));
        std::cout << "help [h]";
    }
}
