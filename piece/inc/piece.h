#pragma once
#include "define.h"
#include "tetromino.h"

namespace gm
{

    class Piece
    {
    public:
        Piece(Tetromino t, int x0, int y0 ,int i);
        Piece()=default;
        bool down();
        bool left();
        bool right();
        bool rotate(int);//1:R 2:180 3:L
        void set_playfield(std::shared_ptr<Matrix> sp);
        std::pair<int,int> get_mino(int i) const;
        std::pair<int,int> get_xy() const;
        int get_color() const;

        bool test(int x,int y) const;
        bool test(int x,int y,int index) const;
        std::pair<int,int> get_mino(int i,int index) const;

        void set_ghost();
        void set_disable();
        Tetromino get_tetromino() const;
    private:
        bool move(int dx,int dy);
        char get_type() const;
    private:
        Tetromino tetro_set;
        int index; //[0 R 2 L]
        int x,y; //正交坐标
        std::shared_ptr<Matrix> sp_playfield;
        int status;//0:阴影 1:正常 2:暂存块
        Offset offset;
    };
}// namespace gm