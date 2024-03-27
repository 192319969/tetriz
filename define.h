#pragma once
#include <string>
#include <chrono>
#include <map>
#include <thread>
#include <iostream>
#include <functional>
#include <locale>
#include <codecvt>
#include <vector>  
#include <memory>
#include <cassert>
#include <ranges>
#include <sstream>
#include <ostream>
#include <queue>
#include <fstream>
#include <cmath>

#ifdef __linux__
#include "termios.h"
#elif  _WIN32
#include <conio.h>
#endif

using namespace std::chrono_literals;
using Matrix = std::vector<std::vector<int>>;
using Tetromino = std::vector<std::vector<std::pair<int,int>>>;
using Offset = std::vector<std::vector<std::pair<int,int>>>;
using std::ranges::views::iota;

#define KEY_Q 'q'
#define KEY_W 'w'
#define KEY_A 'a'
#define KEY_D 'd'
#define KEY_S 's'
#define KEY_Z 'z'
#define KEY_X 'x'
#define KEY_C 'c'
#define KEY_R 'r'
#define KEY_H 'h'
#define KEY_SPACE ' '
