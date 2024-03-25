#pragma once
#include "define.h"
#include "color.h"

namespace gm
{
    using Tetromino_1 = std::vector<std::vector<int>>;
    extern Tetromino_1 I,J,L,O,S,T,Z;

    Tetromino_1 rotate(Tetromino_1& t);
    extern std::map<int, Color> tetro_color;

    //-------------------------------------------
    using Tetromino_2 = std::array<int,4>;
    extern Tetromino_2 I_set,J_set,L_set,O_set,S_set,T_set,Z_set;
    bool get_bit(int t,int i,int j);
    //-------------------------------------------
    /**
     *                      ^y
     *                      |
     *                      |
     *                      |
     *                      |
     *                      |
     *                      |
     *                      |
     * ------------------0--0--0--0------------->x
    */

    extern Tetromino i,j,l,o,s,t,z;
    extern Offset offset,offset_i,offset_o;
}
