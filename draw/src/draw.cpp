#include "draw.h"
#include "terminal.h"
#include "utils.h"
#include "define.h"
#include "piece.h"
#include "game.h"
/*
 	0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
U+250x	─	━	│	┃	┄	┅	┆	┇	┈	┉	┊	┋	┌	┍	┎	┏
U+251x	┐	┑	┒	┓	└	┕	┖	┗	┘	┙	┚	┛	├	┝	┞	┟
U+252x	┠	┡	┢	┣	┤	┥	┦	┧	┨	┩	┪	┫	┬	┭	┮	┯
U+253x	┰	┱	┲	┳	┴	┵	┶	┷	┸	┹	┺	┻	┼	┽	┾	┿
U+254x	╀	╁	╂	╃	╄	╅	╆	╇	╈	╉	╊	╋	╌	╍	╎	╏
U+255x	═	║	╒	╓	╔	╕	╖	╗	╘	╙	╚	╛	╜	╝	╞	╟
U+256x	╠	╡	╢	╣	╤	╥	╦	╧	╨	╩	╪	╫	╬	╭	╮	╯
U+257x	╰	╱	╲	╳	╴	╵	╶	╷	╸	╹	╺	╻	╼	╽	╾	╿

*/
namespace dw{    
    const std::u32string style1=U" ┌┐└┘│─";
    const std::u32string style2=U" ┏┓┗┛┃━";
    const std::u32string style3=U" ╔╗╚╝║═";
    const std::u32string style4=U" ╭╮╰╯│─";
    const std::u32string cur_style=style1;

    //        1,10,12,22
    void window(int top, int left, int width, int height, std::string title)
    {
        for(int row=0;row<height;row++)
        {
            tc::move_to(top+row, ut::block2col(left));
            for(int col=0;col<width;col++)
            {
                if(row==0)//第一行
                {
                    if(col==0)//第一列
                    {
                        std::cout << ut::utf32_to_utf8({cur_style[0] , cur_style[1]});
                    }
                    else if(col==width-1)//最后一列
                    {
                        std::cout << ut::utf32_to_utf8({cur_style[2] , cur_style[0]});
                    }
                    else//中间列
                    {
                        std::cout << ut::utf32_to_utf8({cur_style[6] , cur_style[6]});
                    }
                }
                else if (row==height-1)//最后一行
                {
                    if(col==0)//第一列
                    {
                        std::cout << ut::utf32_to_utf8({cur_style[0] , cur_style[3]});
                    }
                    else if(col==width-1)//最后一列
                    {
                        std::cout << ut::utf32_to_utf8({cur_style[4] , cur_style[0]});
                    }
                    else//中间列
                    {
                        std::cout << ut::utf32_to_utf8({cur_style[6] , cur_style[6]});
                    }
                }
                else//中间行
                {
                    if(col==0)//第一列
                    {
                        std::cout << ut::utf32_to_utf8({cur_style[0] , cur_style[5]});
                    }
                    else if(col==width-1)//最后一列
                    {
                        std::cout << ut::utf32_to_utf8({cur_style[5] , cur_style[0]});
                    }
                    else//中间列
                    {
                        std::cout << "  ";
                    }
                }
            }
        }
        //title
        tc::move_to(top, ut::block2col(left)+width-title.size()/2);
        std::cout << title;
}

void tetromino(gm::Tetromino_1 &t, int top, int left)
{
    for (int i = 0; i < t.size(); i++)
    {
        tc::move_to(top + i, ut::block2col(left));
        for (int j = 0; j < t.size(); j++)
        {
            if (t[i][j] > 0)
            {
                tc::reset_color();
                tc::set_back_color((int)gm::tetro_color[t[i][j]]);
                std::cout << "  ";
                
            }
            else
            {
                tc::reset_color();
                std::cout << "  ";
            }
        }
        
    }
}
void tetromino(gm::Tetromino_2 &t, int top, int left, int index)
{
    for(int i=0;i<4;i++)
    {
        tc::move_to(top+i, ut::block2col(left));

        for(int j=0;j<4;j++)
        {
            if(gm::get_bit(t[index],i,j)){
                tc::reset_color();
                tc::set_back_color(t[index]>>16&0xff);
                std::cout << "  ";
            }
            else{
                tc::reset_color();
                std::cout << "  ";
            }
        }
    }
}
void tetromino(Tetromino &t, int top, int left, int index)
{
    tc::move_to(top, ut::block2col(left));
    tc::set_back_color(t[index][0].second);
    std::cout << "  ";
    for(auto p:t[index]){
        if(p.first>'A') continue;
        //(dx,dy)---->(row,col)
        //row=row-dy
        //col=col+dy
        tc::move_to(top-p.second,ut::block2col(left+p.first));
        std::cout << "  ";
    }
}

void frame(Matrix &frame, int top, int left){
    static Matrix buffer(frame.size(),std::vector<int>(frame[0].size(),-1));
    if(gm::reseting){
        buffer=Matrix(frame.size(),std::vector<int>(frame[0].size(),-1));
    }
    Matrix f(frame.begin(),frame.begin()+20);
    matrix(f,top,left,&buffer,"\u30FB");
}
void next(std::queue<Tetromino> next5,int top, int left){
    static Matrix buffer(15,std::vector<int>(6,-1));
    Matrix next_feild(15,std::vector<int>(6,0));
    for(int y=12;next5.size()>0;y-=3){
        gm::Piece p(next5.front(),2,y,0);
        gm::merge(next_feild,p);
        next5.pop();
    }
    matrix(next_feild,top,left,&buffer);
}
void hold(Tetromino& h,int top, int left){
    static Matrix buffer(4,std::vector<int>(7,-1));
    Matrix hold_feild(4,std::vector<int>(7,0));
    if(!h.empty())
    {
        gm::Piece p(h,3,1,0);
        if(gm::holding){
            p.set_disable();
        }
        gm::merge(hold_feild,p);
        matrix(hold_feild,top,left,&buffer);
    }
}
void matrix(Matrix &m, int top, int left,Matrix* buffer,std::string blank)
{
    std::ostringstream oss;
    // frame xy --------> terminal xy(row/col)
    int row,col;
    for(int y=0;y<m.size();y++)
    {
        for(int x=0;x<m[0].size();x++){
            if(buffer!=nullptr)
            {    
                if((*buffer)[y][x]==m[y][x]) continue;
                (*buffer)[y][x]=m[y][x];
            }
            
            row=m.size()-y-1+top;
            col=x+left;
            tc::move_to(row,ut::block2col(col),oss);
            if(m[y][x]>0){//正常块
                tc::reset_color(oss);
                tc::set_back_color(m[y][x],oss);
                oss << "  ";
            }
            else if(m[y][x]<0){//预览块
                tc::reset_color(oss);
                tc::set_back_color(0-m[y][x],oss);
                oss << "\u25E3\u25E5";
            }
            else{//空白
                tc::reset_color(oss);
                oss << blank;
            }
        }
    }
    std::cout << oss.str();
}
}