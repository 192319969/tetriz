#pragma once
#include "define.h"
#include "piece.h"
#include "tetromino.h"

namespace gm
{
    class Field
    {
    public:
        //��Ϸ��ѭ������Ⱦÿһ֡
        void process();
        //��Ⱦһ֡
        void render();
        //��Ԥ��������ȡ��һ������
        Piece pick();
        //����
        void lock();
        //������
        void clear();
        //��ʼ����Ϸ
        void init();
        //�˳���Ϸ
        void quit();
        void rotate(int);
        void left();
        void right();
        void down();
        //ֱ��
        void drop();
        //����Ԥ������
        void preview();
        //����Ԥ���ͼ
        void load();
        //�ݴ�
        void hold();
        //����
        void levelup();
        //����
        void reset();
        //����
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