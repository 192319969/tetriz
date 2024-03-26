#pragma once
#include "tetromino.h"
#include "piece.h"
#include <chrono>
#include <queue>

namespace gm    
{
    //================================================================
    //  游戏变量定义
    //================================================================
    //游戏运行状态
    extern bool running;
    //锁定标志
    extern bool locking;
    //暂存标志
    extern bool holding;
    //暂存标志
    extern bool reseting;
    //结束标志
    extern bool ending;
    //帮助标志
    extern bool helping;
    //当前正在下落的方块
    extern Piece one_piece;
    //游戏区域

    extern Matrix playfield;
    //每一帧的时间间隔
    extern std::chrono::microseconds duration;
    //当前渲染帧
    extern Matrix frame;
    //五格预览队列
    extern std::queue<Tetromino> next;
    //暂存
    extern Tetromino hold_piece;
    //游戏分数
    extern int score,level,lines;
    //================================================================
    //  游戏逻辑
    //================================================================

    //游戏主循环，渲染每一帧
    void process();
    //渲染一帧
    void render();
    //从预览队列中取出一个方块
    Piece pick();
    //锁定
    void lock();
    //消除行
    void clear();
    //初始化游戏
    void init();
    //退出游戏
    void quit();
    void rotate(int);
    void left();
    void right();
    void down();
    //直落
    void drop();
    //生成预览队列
    void preview();
    //载入预设地图
    void load();
    //暂存
    void hold();
    //升级
    void levelup();
    //重置
    void reset();
    //帮助
    void help();
    //--------------------------------------
    void merge(Matrix& m,const Piece& p);

}
/**
 *      https://harddrop.com/wiki/Scoring
 * 
 * Single	100 x level	
 * Double	300 x level	
 * Triple	500 x level	
 * Tetris	800 x level	
 * Soft drop	1 point per cell	
 * Hard drop	2 points per cell	
**/