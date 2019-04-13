#include "block.h"
#include <QTime>


Block::Block(int _row ,int _col,int _boomNum):
    row(_row),
    col(_col),
    boomNum(_boomNum),
    timeNum(0),
    redFlagNum(_boomNum)
{
    init();
}
void Block::init()
{
    //创建二维数组
    p = new int *[row];
    for(int i = 0;i < row; ++i)
    {
        p[i]=new int[col];
    }
    //初始二维数组
    for(int i = 0;i < row; ++i)
    {
        for(int j = 0; j< col;++j)
        {
            p[i][j]=0;
        }
    }
    //产生随机数炸弹，并标记为99
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i =0;i<boomNum;++i)
    {
//        int num = qrand() % (row*col) -1 ;
//        int rowBlock = num / row;
//        int colBlock = num % col;
        int rowBlock = qrand() % row;
        int colBlock = qrand() % col;
        if(p[rowBlock][colBlock] == 99)
        {
            i--;
            continue;
        }
        else
            p[rowBlock][colBlock] = 99;
//        cout<<rowBlock<<colBlock<<p[rowBlock][colBlock];
    }
    //为除炸弹块外赋值，中间块表示周围八个位置的炸弹数
    for(int i =0;i <row;++i)
    {
        for(int j=0;j<col;++j)
        {
            if(p[i][j]!=99)
            {
                int boomBlockNum=0;
                for(int blockRow=i-1;blockRow<=i+1;++blockRow)
                {
                    for(int blockCol=j-1;blockCol<=j+1;++blockCol)
                    {
                        //边界处理
                        if(blockRow<0||blockRow>=row||blockCol<0||blockCol>=col)
                            continue;
                        //检测雷的数目
                        if(p[blockRow][blockCol]==99)
                            boomBlockNum++;
                    }
                }
                p[i][j]=boomBlockNum;
            }
//            cout<<p[i][j];
        }
    }
}

Block::~Block()
{
    for(int i =0 ;i<row;++i)
    {
        delete[] p[i];
    }
    delete[] p;
}

int Block::getcol() const
{
    return this->col;
}
int Block::getrow() const
{
    return this->row;
}
int Block::getboomNum() const
{
    return boomNum;
}
int Block::gettimeNum() const
{
    return timeNum;
}
int Block::getredFlagNum() const
{
    return redFlagNum;
}
void Block::addtimeNum()
{
    timeNum = timeNum + 1;
}
void Block::minusredFlagNum()
{
    redFlagNum = redFlagNum -1;
}
void Block::addredFlagNum()
{
     redFlagNum = redFlagNum + 1;
}
