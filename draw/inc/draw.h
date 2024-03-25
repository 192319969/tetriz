#pragma once
#include <string>
#include "tetromino.h"
/*

ui: layout
dw: draw             gm: game logic     ut: utils
tc: terminal control

*/
namespace dw
{

    void window(int top,int left, int width, int height,std::string title);
    // void tetromino(gm::Tetromino_1 &t, int top, int left);
    // void tetromino(gm::Tetromino_2 &t, int top, int left,int index);
    void tetromino(Tetromino &t, int top, int left,int index);
    void frame(Matrix &frame, int top, int left);
    void next(std::queue<Tetromino> next5,int top, int left);
    void matrix(Matrix &m, int top, int left,Matrix* buffer=nullptr,std::string blank="  ");

}