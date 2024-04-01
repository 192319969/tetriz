#pragma once
#include "define.h"
#include "piece.h"
#include "tetromino.h"

namespace gm
{
    class Field
    {
    public:
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
    private:
        bool running;
        bool locking;
        bool holding;
        bool reseting;
        bool ending;
        bool helping;
        Piece one_piece;
        Matrix field,frame;
        std::chrono::microseconds duration;
        std::queue<Tetromino> next;
        Tetromino hold_piece;
        int score,lines,level;
        std::vector<bool> isTrashLine(10,false);
    };
}