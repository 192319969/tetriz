#include "game.h"
#include "tetromino.h"
#include "utils.h"
#include "define.h"

namespace gm{
    //---------------------------变量定义区------------------------
    bool running,locking,holding;
    Piece one_piece;
    Matrix playfield;
    std::chrono::microseconds duration;
    Matrix frame;
    std::queue<Tetromino> next;
    Tetromino hold_piece;
    int score,level,lines;
    bool ending;
    bool reseting;
    bool helping;
    //-------------------------------------------------------------
    void init()
    {
        srand(std::time(0));
        running=true;
        locking=false;
        holding=false;
        ending=false;
        reseting=false;
        helping=false;
        score=0;
        lines=0;
        levelup();
        //playfield[y][x],x=0~9,y=0~21, 10*20
        playfield=Matrix(22,std::vector<int>(10,0));
        load();
        preview();
        one_piece=pick();
        frame=playfield;
    }

    void process()
    {
        if(ending)
        {
            return;
        }
        render();
        if(ut::timer(duration))
        {
            if(one_piece.down())
                return;
            //如果无法继续下落，就锁定
            if(locking)
            {
                lock();
            //消除行
                clear();
                one_piece=pick();
                levelup();
                locking=false;
                holding=false;
                reseting=false;
            }else{
                locking=true;
            }
        }
    }

    void render()
    {
        frame=playfield;
        // auto [x,y]=one_piece.get_xy();
        // //姝ｅ父鍧楁覆鏌?
        // for(auto i:iota(0,4))
        // {
        //     auto [dx,dy]=one_piece.get_mino(i);
        //     frame[y+dy][x+dx]=one_piece.get_color();
        // }
        // //棰勮?堝潡娓叉煋
        merge(frame,one_piece);
        Piece ghost = one_piece;
        ghost.set_ghost();
        // while(one_piece.test(x,--y));
        // y++;

        while(ghost.down())
            ;
        merge(frame,ghost);
        // for(auto i:iota(0,4))
        // {
        //     auto [dx,dy]=one_piece.get_mino(i);
        //     if(frame[y+dy][x+dx]==0)
        //         frame[y+dy][x+dx]=0-one_piece.get_color();
        // }
    }
    //锁定
    void lock(){
        merge(playfield,one_piece);
    }
    void clear()
    {
        int count=0;
        for(auto it=playfield.begin();it != playfield.end();++it){
            bool full=true;
            for(auto cell:*it){
                if(cell==0){
                    full=false;
                    break;
                }
            }
            if(full){
                it = playfield.erase(it);
                playfield.push_back(std::vector<int>(it->size(),0));
                it--;
                count++;
            }
        }
        switch(count){
            case 1:
                score+=100*level;
                break;
            case 2:
                score+=300*level;
                break;
            case 3:
                score+=500*level;
                break;
            case 4:
                score+=800*level;
                break;
            default:
                break;
        }
        lines+=count;
    }
    Piece pick()
    {
        //TODO: 从5格预览队列中拿去第一个元素
        // static std::vector<Tetromino> bag{i,j,l,o,s,t,z};
        // Piece p(bag[rand()%7],4,20,0);
        // p.set_playfield(std::make_shared<Matrix>(playfield));
        assert(next.size()>0);
        Piece p(next.front(),4,20,0);
        // Piece p(j,4,20,0);
        p.set_playfield(std::make_shared<Matrix>(playfield));
        if(!p.test(4,20))
        {
            ending=true;
        }
        next.pop();
        preview();
        return std::move(p);
    }
    void quit()
    {
        running=false;
    }
    void rotate(int i)
    {
        one_piece.rotate(i);
    }
    void left()
    {
        one_piece.left();
    }
    void right()
    {
        one_piece.right();
    }
    void down()
    {
        if(one_piece.down())
            score++;
    }
    void drop()
    {
        while(one_piece.down())
            score+=2;
        locking=true;
    }
    void preview(){
        static std::vector<Tetromino> bag{i,j,l,o,s,t,z};
        int index;
        while(next.size()<5){
            index=rand()%bag.size();
            next.push(bag[index]);
            bag.erase(bag.begin()+index);
            if(bag.size()==0)
                bag={i,j,l,o,s,t,z};
        }
    }
    void load()
    {
        std::ifstream fs("tetriz.map");
        assert(fs.is_open());
        std::string line;
        for(auto& row:playfield|std::ranges::views::take(20)|std::ranges::views::reverse){
            getline(fs,line);
            for(auto i:iota(0,10)){
                if(line[i]=='1')
                {
                    row[i]=(int)Color::Gray;
                }
            }
        }
        fs.close();
    }
    //如果暂存区为空，当前块放入暂存区，重新生成一个当前块，从头开始掉落
    //如果暂存区不为空，当前块放入暂存区，使用原暂存区的块重新生成一个当前块，从头开始掉落
    //每回合只可以暂存一次
    void hold()
    {
        if(holding)
            return;
        if(hold_piece.empty()){
            hold_piece=one_piece.get_tetromino();
            one_piece=pick();
            one_piece.set_playfield(std::make_shared<Matrix>(playfield));
        }else{
            auto tmp = hold_piece;
            hold_piece=one_piece.get_tetromino();
            one_piece = Piece(tmp,4,20,0);
            one_piece.set_playfield(std::make_shared<Matrix>(playfield));
        }
        holding=true;
    }
    void levelup()
    {
        // (0.8-((Level-1)*0.007))^(Level-1)
        level=lines/10+1;
        duration=std::chrono::milliseconds((int)(pow(0.8-(level-1)*0.007,level-1)*1000));
    }
    void reset(){
        init();
        reseting=true;
    }
    void help()
    {

    }
    void merge(Matrix &m, const Piece &p)
    {
        auto [x,y]=p.get_xy();
        for(auto i:iota(0,4)){
            auto [dx,dy]=p.get_mino(i);
            if(m[y+dy][x+dx]==0)
                m[y+dy][x+dx]=p.get_color();
        }
    }
}