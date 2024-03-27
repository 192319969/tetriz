#include "tetromino.h"

namespace gm
{
/*
    Tetromino_1 I{
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    Tetromino_1 L{{0,0,2},{2,2,2},{0,0,0}};
    Tetromino_1 O{{0,3,3},{0,3,3},{0,0,0}};
    Tetromino_1 J{{4,0,0},{4,4,4},{0,0,0}};
    Tetromino_1 S{{0,5,5},{5,5,0},{0,0,0}};
    Tetromino_1 T{{0,6,0},{6,6,6},{0,0,0}};
    Tetromino_1 Z{{7,7,0},{0,7,7},{0,0,0}};
*/
    std::map<int, Color> tetro_color{
        {1, Color::Cyan},
        {2, Color::Orange},
        {3, Color::Yellow},
        {4, Color::Blue},
        {5, Color::Green},
        {6, Color::Purple},
        {7, Color::Red}
    };
/*
    Tetromino_1 rotate(Tetromino_1 &t)
    {
        Tetromino_1 result(t.size(), std::vector<int>(t.size(), 0));
        for (int i = 0; i < t.size(); i++)
        {
            //t[i][j]=t'[j][3-i-1]
            for (int j = 0; j < t.size(); j++)
            {
                if(t[i][j]>0)
                    result[j][t.size()-i-1] = t[i][j];
            }
        }
        return std::move(result);
    }
    bool get_bit(int t, int i, int j)
    {
        return (t>>(i*4+j))&0x1==1;
    }
*/
    /**
     * i
     * 0000  0010  0000  0100
     * 1111  0010  0000  0100
     * 0000  0010  1111  0100
     * 0000  0010  0000  0100
     *
     * 0x0f00 0x2222 0x00f0 0x4444
     *
     * []<<name char 'i'
     * []<<color
     * []<<data
     * []<<data
     */
/*
    Tetromino_2 I_set{
        0x0f00 | (int)Color::Cyan<<16 | 'I'<<24,
        0x2222 | (int)Color::Cyan<<16 | 'I'<<24, 
        0x00f0 | (int)Color::Cyan<<16 | 'I'<<24, 
        0x4444 | (int)Color::Cyan<<16 | 'I'<<24,
    };
*/
    /**
     * o
     * 0000
     * 0110
     * 0110
     * 0000
     * 
     * 0x0660
    */
/*
    Tetromino_2 O_set{
        0x0660 | (int)Color::Yellow<<16 | 'O'<<24,
        0x0660 | (int)Color::Yellow<<16 | 'O'<<24,
        0x0660 | (int)Color::Yellow<<16 | 'O'<<24,
        0x0660 | (int)Color::Yellow<<16 | 'O'<<24,
    };
*/
    //-------------------------------------------------
    Tetromino i{{
        {{{ 'I', (int)Color::Cyan},{-1, 0},{ 1, 0},{ 2, 0}}},//0
        {{{ 'I', (int)Color::Cyan},{ 0, 1},{ 0,-1},{ 0,-2}}},//R
        {{{ 'I', (int)Color::Cyan},{-2, 0},{-1, 0},{ 1, 0}}},//2
        {{{ 'I', (int)Color::Cyan},{ 0, 2},{ 0, 1},{ 0,-1}}}//L
    }};
    Tetromino j{{
        {{{ 'J', (int)Color::Blue},{-1, 1},{-1, 0},{ 1, 0}}},//0
        {{{ 'J', (int)Color::Blue},{ 1, 1},{ 0, 1},{ 0,-1}}},//R
        {{{ 'J', (int)Color::Blue},{-1, 0},{ 1, 0},{ 1,-1}}},//2
        {{{ 'J', (int)Color::Blue},{ 0, 1},{-1,-1},{ 0,-1}}}//L
    }};
    Tetromino l{{
        {{{ 'L', (int)Color::Orange},{-1, 0},{ 1, 0},{ 1, 1}}},//0
        {{{ 'L', (int)Color::Orange},{ 0, 1},{ 0,-1},{ 1,-1}}},//R
        {{{ 'L', (int)Color::Orange},{-1,-1},{-1, 0},{ 1, 0}}},//2
        {{{ 'L', (int)Color::Orange},{-1, 1},{ 0, 1},{ 0,-1}}}//L
    }};
    Tetromino o{{
        {{{ 'O', (int)Color::Yellow},{ 0, 1},{ 1, 1},{ 1, 0}}},//0
        {{{ 'O', (int)Color::Yellow},{ 0,-1},{ 1, 0},{ 1,-1}}},//R
        {{{ 'O', (int)Color::Yellow},{-1,-1},{-1, 0},{ 0,-1}}},//2
        {{{ 'O', (int)Color::Yellow},{-1, 1},{-1, 0},{ 0, 1}}}//L
    }}; 
    Tetromino s{{
        {{{ 'S', (int)Color::Green},{-1, 0},{ 0, 1},{ 1, 0}}},//0
        {{{ 'S', (int)Color::Green},{ 0, 1},{ 1, 0},{ 0,-1}}},//R
        {{{ 'S', (int)Color::Green},{-1, 0},{ 1, 0},{ 0,-1}}},//2
        {{{ 'S', (int)Color::Green},{-1, 0},{ 0, 1},{ 0,-1}}}//L
    }};
    Tetromino t{{
        {{{ 'T', (int)Color::Purple},{-1, 0},{ 0, 1},{ 1, 0}}},//0
        {{{ 'T', (int)Color::Purple},{ 0, 1},{ 1, 0},{ 0,-1}}},//R
        {{{ 'T', (int)Color::Purple},{-1, 0},{ 1, 0},{ 0,-1}}},//2
        {{{ 'T', (int)Color::Purple},{-1, 0},{ 0, 1},{ 0,-1}}}//L
    }};
    Tetromino z{{
        {{{ 'Z', (int)Color::Red},{-1, 1},{ 0, 1},{ 1, 0}}},//0
        {{{ 'Z', (int)Color::Red},{ 1, 1},{ 1, 0},{ 0,-1}}},//R
        {{{ 'Z', (int)Color::Red},{-1, 0},{ 0,-1},{ 1,-1}}},//2
        {{{ 'Z', (int)Color::Red},{-1,-1},{-1, 0},{ 0, 1}}}//L
    }};
    Offset offset{{
        {{{ 0, 0},{ 0, 0},{ 0, 0},{ 0, 0},{ 0, 0}}},//0
        {{{ 0, 0},{ 1, 0},{ 1,-1},{ 0, 2},{ 1, 2}}},//R
        {{{ 0, 0},{ 0, 0},{ 0, 0},{ 1, 0},{ 0, 0}}},//2
        {{{ 0, 0},{-1, 0},{-1, 1},{ 0, 2},{-1, 2}}} //L
    }};
    Offset offset_i{{
        {{{ 0, 0},{-1, 0},{ 2, 0},{-1, 0},{ 2, 0}}},//0
        {{{-1, 0},{ 0, 0},{ 0, 0},{ 0, 1},{ 0,-2}}},//R
        {{{-1, 1},{ 1, 1},{-2, 1},{ 1, 0},{-2, 0}}},//2
        {{{ 0, 1},{ 0, 1},{ 0, 1},{ 0,-1},{ 0, 2}}} //L
    }};
    Offset offset_o{{
        {{{ 0, 0}}},//0
        {{{ 0,-1}}},//R
        {{{-1,-1}}},//2
        {{{-1, 0}}} //L
    }};
}








