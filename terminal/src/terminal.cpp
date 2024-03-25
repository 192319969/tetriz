#include "terminal.h"
#include <iostream>

#define CSI "\033["

void tc::move_to(int row, int col, std::ostream &os)
{
    os << CSI << row << ';' << col << 'H';
}

void tc::set_fore_color(int id, std::ostream &os)
{
    os << CSI << "38;5;" << id << 'm';
}

void tc::set_back_color(int id, std::ostream &os)
{
    os << CSI << "48;5;" << id << 'm';
}

void tc::clear_screen(std::ostream &os)
{
    os << CSI << "2J";
}

void tc::reset_color(std::ostream &os)
{
    os << CSI << "0m";
}

void tc::hide_cursor(std::ostream &os)
{
    os << CSI << "?25l";
}

void tc::show_cursor(std::ostream &os)
{
    os << CSI << "?25h";
}
