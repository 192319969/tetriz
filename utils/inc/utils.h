#pragma once
#include <string>
#include <define.h>

namespace ut
{
    int fps();
    std::string utf32_to_utf8(std::u32string str);

    inline int block2col(int block)
    {
        return block * 2 - 1;
    }
    bool timer(std::chrono::microseconds sec, int player = 1);
}