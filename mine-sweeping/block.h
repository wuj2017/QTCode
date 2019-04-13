#ifndef BLOCK_H
#define BLOCK_H

#include <QDebug>

#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

class Block
{
public:
    Block(int _row ,int _col,int _boomNum);
    ~Block();
    int getcol() const;
    int getrow() const;
    int getboomNum() const;
    int getredFlagNum() const;
    int gettimeNum()const;
    void minusredFlagNum();
    void addredFlagNum();
    void addtimeNum();
    int **p;
    void init();
private:
    int row,col,boomNum;//行，列，雷数
    int timeNum,redFlagNum;

};

#endif // BLOCK_H
