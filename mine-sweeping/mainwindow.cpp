#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include <QMessageBox>

#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"
//定义全局变量
static int paint_flag = 0; //0-第一次绘制雷区;2-点击到空白;3-右键点击绘制;4-踩到雷;5-游戏成功
QPainter* paintmywindow;
MainWindow * app;
//初始化类,现在为初级
int ROW =9;
int COL =9;
int BOOMNUM = 10;
Block* mine = new Block(ROW,COL,BOOMNUM);
int click_x,click_y;
bool gameOver = false,timeOut = true;
int LENGTH=mine->getcol()*21;
int HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
static bool showimage = true;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    app=this;
    ui->setupUi(this);
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
    runtime = new QTimer(this);
    connect(runtime,SIGNAL(timeout()),this,SLOT(on_secondadd()));
    connect(runtime,SIGNAL(timeout()),this,SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    paintmywindow = &painter;
    //加载位图
    QPixmap mine_title("./mine_title.bmp");
    QPixmap block_close("./block_close.bmp");
    QPixmap block_open("./block_open.bmp");
    QPixmap red_flag("./redflag.bmp");
    QPixmap keil_boom("./keilboom.bmp");
    QPixmap click_boom("./clickboom.bmp");
    QPixmap boom("./boom.bmp");
    QPixmap qq_smile("./smile.bmp");
    QPixmap qq_lose("./lose.bmp");
    QPixmap qq_pround("./proud.bmp");
    QPixmap ele_0("./ele0.bmp");
    QPixmap ele_1("./ele1.bmp");
    QPixmap ele_2("./ele2.bmp");
    QPixmap ele_3("./ele3.bmp");
    QPixmap ele_4("./ele4.bmp");
    QPixmap ele_5("./ele5.bmp");
    QPixmap ele_6("./ele6.bmp");
    QPixmap ele_7("./ele7.bmp");
    QPixmap ele_8("./ele8.bmp");
    QPixmap ele_9("./ele9.bmp");
    QPixmap blk_1("./blk1.bmp");
    QPixmap blk_2("./blk2.bmp");
    QPixmap blk_3("./blk3.bmp");
    QPixmap blk_4("./blk4.bmp");
    QPixmap blk_5("./blk5.bmp");
    QPixmap blk_6("./blk6.bmp");
    QPixmap blk_7("./blk7.bmp");
    QPixmap blk_8("./blk8.bmp");


    //每个雷块存储0-8范围内的数值，设为X
    //    0-8         -----      该块周围雷数（未翻开）     X
    //    50-58       -----      该块有红旗,但不是雷。             X+50
    //    100-108     -----      该块周围雷数（已翻开）     X+100
    //    99          -----      该块为雷
    //    145         -----      该块为雷且有红旗

    if(0==paint_flag)
    {
        painttitle(paintmywindow);
        //绘制雷区
        for(int i=0;i<mine->getrow();++i)
        {
            for(int j=0;j<mine->getcol();++j)
                painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
        }
    }
    //左键点击到炸弹
    else if(4==paint_flag)
    {
        painttitle(paintmywindow);
        //绘制雷区
        for(int i=0;i<mine->getrow();++i)
        {
            for(int j=0;j<mine->getcol();++j)
            {
                if(mine->p[i][j]<=8)
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                else if(mine->p[i][j]==99)
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                else if(mine->p[i][j]==149)
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                    //cout<<i<<j;
                }

                else if(mine->p[i][j]>=50&&mine->p[i][j]<=58)
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,keil_boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                else if(mine->p[i][j]>=100 && mine->p[i][j]<=108)
                {
                    int blk_num = mine->p[i][j]-100;
                    switch(blk_num)
                    {
                    case 0:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 1:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_1,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 2:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_2,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 3:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_3,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 4:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_4,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 5:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_5,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 6:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_6,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 7:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_7,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    case 8:painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_8,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                    }
                }
            }
        }
        //绘制点击到的雷
        painter.drawPixmap(click_x*BLOCK_LENGTH,click_y*BLOCK_HEIGH+TITILE_HEIGH,click_boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
    }
    //左键点击到空白
    else if(2==paint_flag)
    {
        painttitle(paintmywindow);
        paintboom(paintmywindow);
    }
    //右键点击绘制
    else if(3==paint_flag)
    {
        painttitle(paintmywindow);
        paintboom(paintmywindow);
    }
    //游戏成功结束
    else if(5==paint_flag)
    {
        painttitle(paintmywindow);
        paintboom(paintmywindow);
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //单击获取鼠标当前落点，修改雷块信息，判断左右键
    click_x = event->x();
    click_y = event->y();

//    cout<<click_x<<click_y<<TITILE_HEIGH;

    //判断是否单击了笑脸
//    if(event->buttons()==Qt::LeftButton && (click_x>LENGTH/2-12) &&
//            (click_x<LENGTH/2+12) && (click_y>7+TTILE_BEGIN) && (click_y<7+TTILE_BEGIN+EXPRESSION_HEIGH))
    if(event->buttons()==(Qt::LeftButton)&&(click_x>(int)LENGTH*100/200-11)&&
            (click_x<(int)LENGTH*100/200+11 +EXPRESSION_LENGHT)&&(click_y>7+TTILE_BEGIN)&&
            (click_y<7+TTILE_BEGIN+EXPRESSION_HEIGH))
    {
        cout<<"Click the smile";
        restart(mine->getrow(),mine->getcol(),mine->getboomNum());
        paint_flag=0;
        gameOver =false;
        timeOut = true;
        runtime->stop();
        update();
        return;//后加的
    }
    else if(click_y<TITILE_HEIGH)
        return;

    if(gameOver)
        return;
    //确定落点
    click_x = click_x/BLOCK_LENGTH;
    click_y = (click_y-TITILE_HEIGH)/BLOCK_HEIGH;

//    cout<<click_x<<click_y;

    //如果点击了左键
    if(event->buttons()==Qt::LeftButton)
    {
        if(timeOut)
        {
            runtime->start(1000);
            timeOut = false;
        }
        //点到雷，瞬间爆炸
        if(mine->p[click_y][click_x]==99)
        {
            paint_flag=4;
            timeOut=true;
            gameOver = true;
            runtime->stop();
            update();
        }
        else if(mine->p[click_y][click_x]<=8)
        {
            showblock(click_y,click_x);
            paint_flag = 2;
            if(gameOver=isWin())
            {
                paint_flag = 5;
                timeOut = true;
                runtime->stop();
            }
            update();
            if(gameOver)
            {
                if(showimage)
                {
                    QMessageBox message(QMessageBox::NoIcon,"You are win","Very good,I really appreciate you");
                    message.setIconPixmap(QPixmap("win.png"));
                    showimage = false;
                    message.exec();
                }
                else
                {
                    //////////
                }
            }
        }
        else return;
    }
    else if(event->buttons() == Qt::RightButton)
    {
        //如果点击了右键
        if(mine->p[click_y][click_x]<=8 || mine->p[click_y][click_x]==99)
        {
            mine->p[click_y][click_x]+=50;

//            cout<<":"<<click_x<<click_y<<mine->p[click_y][click_x];

            mine->minusredFlagNum();
        }
        else if(mine->p[click_y][click_x]>=50 && mine->p[click_y][click_x]<=58 || mine->p[click_y][click_x]==149)
        {
            mine->p[click_y][click_x] -=50;
            mine->addredFlagNum();
        }
        paint_flag=3;
        if(gameOver=isWin())
        {
            paint_flag=5;
            timeOut=true;
            runtime->stop();
        }
        update();
        if(gameOver)
        {
            if(showimage)
            {
                QMessageBox message(QMessageBox::NoIcon,"You are win","Very good,I really appreciate you");
                message.setIconPixmap(QPixmap("win.png"));
                showimage = false;
                message.exec();
            }
            else
            {
                /////
            }
        }
    }
}

void painttitle(QPainter *painter)
{
    //加载位图
    QPixmap mine_title("./mine_title.bmp");
    QPixmap qq_smile("./smile.bmp");
    QPixmap qq_lose("./lose.bmp");
    QPixmap qq_pround("./proud.bmp");
    QPixmap ele_0("./ele0.bmp");
    QPixmap ele_1("./ele1.bmp");
    QPixmap ele_2("./ele2.bmp");
    QPixmap ele_3("./ele3.bmp");
    QPixmap ele_4("./ele4.bmp");
    QPixmap ele_5("./ele5.bmp");
    QPixmap ele_6("./ele6.bmp");
    QPixmap ele_7("./ele7.bmp");
    QPixmap ele_8("./ele8.bmp");
    QPixmap ele_9("./ele9.bmp");
    QPixmap ele_10("./ele10.bmp");
    QPixmap blk_1("./blk1.bmp");
    QPixmap blk_2("./blk2.bmp");
    QPixmap blk_3("./blk3.bmp");
    QPixmap blk_4("./blk4.bmp");
    QPixmap blk_5("./blk5.bmp");
    QPixmap blk_6("./blk6.bmp");
    QPixmap blk_7("./blk7.bmp");
    QPixmap blk_8("./blk8.bmp");
    //调整尺寸大小
    mine_title = mine_title.scaled(QSize(LENGTH,40));
    //显示标题
    painter->drawPixmap(0,TTILE_BEGIN,mine_title,0,0,1000,1000);

    if(paint_flag==4)
        painter->drawPixmap(LENGTH/2-11,7+TTILE_BEGIN,qq_lose,0,0,1000,1000);
    else if(paint_flag==5)
        painter->drawPixmap(LENGTH/2-11,7+TTILE_BEGIN,qq_pround,0,0,1000,1000);
    else
        painter->drawPixmap(LENGTH/2-11,7+TTILE_BEGIN,qq_smile,0,0,1000,1000);

    //显示红旗
    int redflagnum = mine->getredFlagNum();
    if(redflagnum <0)
    {
        redflagnum= -redflagnum;
        painter->drawPixmap(LENGTH/5-30,5+TTILE_BEGIN,ele_10,0,0,1000,1000);
    }
    else
        painter->drawPixmap(LENGTH/5-30,5+TTILE_BEGIN,ele_0,0,0,1000,1000);

    for(int i=2;i>0;i--)
    {
        switch(redflagnum % 10)
        {
        case 0:  painter->drawPixmap((int)(LENGTH*40)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
        case 1:  painter->drawPixmap((int)(LENGTH*40)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
        case 2:  painter->drawPixmap((int)(LENGTH*40)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
        case 3:  painter->drawPixmap((int)(LENGTH*40)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
        case 4:  painter->drawPixmap((int)(LENGTH*40)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
        case 5:  painter->drawPixmap((int)(LENGTH*40)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
        case 6:  painter->drawPixmap((int)(LENGTH*40)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
        case 7:  painter->drawPixmap((int)(LENGTH*40)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
        case 8:  painter->drawPixmap((int)(LENGTH*40)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
        case 9:  painter->drawPixmap((int)(LENGTH*40)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
        }
        redflagnum = redflagnum/10;
    }

    //显示时间
    int timenum = mine->gettimeNum();
    for(int i =2;i>=0;i--)
    {
        switch(timenum % 10)
        {
        case 0:  painter->drawPixmap((int)(LENGTH*163)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_0,0,0,1000,1000);break;
        case 1:  painter->drawPixmap((int)(LENGTH*163)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_1,0,0,1000,1000);break;
        case 2:  painter->drawPixmap((int)(LENGTH*163)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_2,0,0,1000,1000);break;
        case 3:  painter->drawPixmap((int)(LENGTH*163)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_3,0,0,1000,1000);break;
        case 4:  painter->drawPixmap((int)(LENGTH*163)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_4,0,0,1000,1000);break;
        case 5:  painter->drawPixmap((int)(LENGTH*163)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_5,0,0,1000,1000);break;
        case 6:  painter->drawPixmap((int)(LENGTH*163)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_6,0,0,1000,1000);break;
        case 7:  painter->drawPixmap((int)(LENGTH*163)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_7,0,0,1000,1000);break;
        case 8:  painter->drawPixmap((int)(LENGTH*163)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_8,0,0,1000,1000);break;
        case 9:  painter->drawPixmap((int)(LENGTH*163)/200-30+i*ELENUM_LENGHT,5+TTILE_BEGIN,ele_9,0,0,1000,1000);break;
        }
        timenum/=10;
    }
}

//绘制鼠标点击后的雷区
void paintboom(QPainter *painter)
{
    //加载位图
    QPixmap mine_title("./mine_title.bmp");
    QPixmap block_close("./block_close.bmp");
    QPixmap block_open("./block_open.bmp");
    QPixmap red_flag("./redflag.bmp");
    QPixmap keil_boom("./keilboom.bmp");
    QPixmap click_boom("./clickboom.bmp");
    QPixmap boom("./boom.bmp");
    QPixmap qq_smile("./smile.bmp");
    QPixmap qq_lose("./lose.bmp");
    QPixmap qq_pround("./proud.bmp");
    QPixmap ele_0("./ele0.bmp");
    QPixmap ele_1("./ele1.bmp");
    QPixmap ele_2("./ele2.bmp");
    QPixmap ele_3("./ele3.bmp");
    QPixmap ele_4("./ele4.bmp");
    QPixmap ele_5("./ele5.bmp");
    QPixmap ele_6("./ele6.bmp");
    QPixmap ele_7("./ele7.bmp");
    QPixmap ele_8("./ele8.bmp");
    QPixmap ele_9("./ele9.bmp");
    QPixmap ele_10("./ele10.bmp");
    QPixmap blk_1("./blk1.bmp");
    QPixmap blk_2("./blk2.bmp");
    QPixmap blk_3("./blk3.bmp");
    QPixmap blk_4("./blk4.bmp");
    QPixmap blk_5("./blk5.bmp");
    QPixmap blk_6("./blk6.bmp");
    QPixmap blk_7("./blk7.bmp");
    QPixmap blk_8("./blk8.bmp");



    for(int i =0;i<mine->getrow();i++)
    {
        for(int j=0;j<mine->getcol();j++)
        {
            if(mine->p[i][j]<=8 || mine->p[i][j]==99)//该块信息未修改
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            else if(mine->p[i][j]>=50 && mine->p[i][j] <= 58 || mine->p[i][j]==149) //该雷块已经被修改，且被标记为小红旗
            {
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
//                cout<<i<<j<<mine->p[i][j];
            }
            else if(mine->p[i][j]>=100 && mine->p[i][j]<=108) //该雷块已经被修改，该数值减去100即为该雷块周围的雷数
            {
                int blk_num = mine->p[i][j]-100;
                switch (blk_num)
                {
                case 0:painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 1:painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_1,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 2:painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_2,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 3:painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_3,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 4:painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_4,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 5:painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_5,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 6:painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_6,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 7:painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_7,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                case 8:painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,blk_8,0,0,BLOCK_LENGTH,BLOCK_HEIGH);break;
                }
            }
        }
    }
}

void restart(int row, int col, int boomnum)
{
    mine = new Block(row,col,boomnum);
}
void showblock(int x, int y)
{
    for(int blockRow=x-1;blockRow<=x+1;++blockRow)
    {
        for(int blockCol=y-1;blockCol<=y+1;++blockCol)
        {
            if(blockCol<0||blockRow<0||blockCol>=mine->getcol()||blockRow >= mine->getrow())
                continue;
            if(mine->p[blockRow][blockCol]<=8)
            {
                mine->p[blockRow][blockCol]+=100;
                if( mine->p[blockRow][blockCol]==100)
                    showblock(blockRow,blockCol);
            }
        }
    }
}
bool isWin()
{
    int cnt = 0;
    for(int row = 0; row <mine->getrow();row++)
        for(int col =0;col<mine->getcol();col++)
        {
            if((mine->p[row][col]>=100)&&(mine->p[row][col]<110))
                cnt++;
        }
    if(cnt>=((mine->getcol()*mine->getrow())-mine->getboomNum()))
        return true;
    else
        return false;
}

//计时器槽函数
void MainWindow::on_secondadd()
{
    mine->addtimeNum();
}


void MainWindow::on_actionprimary_triggered()
{
    gameOver = false;
    timeOut = true;
    mine = new Block(9,9,10);
    LENGTH = mine->getcol()*21;
    HEIGHT = mine->getrow()*21+TITILE_HEIGH;
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);

}

void MainWindow::on_actionMiddle_triggered()
{
    gameOver = false;
    timeOut = true;
    mine = new Block(16,16,40);
    LENGTH = mine->getcol()*21;
    HEIGHT = mine->getrow()*21 + TITILE_HEIGH;
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
}

void MainWindow::on_actionSenor_triggered()
{
    gameOver = false;
    timeOut = true;
    mine = new Block(16,30,99);
    LENGTH = mine->getcol()*21;
    HEIGHT = mine->getrow()*21 + TITILE_HEIGH;
    this->setMinimumSize(LENGTH,HEIGHT);
    this->setMaximumSize(LENGTH,HEIGHT);
}

void MainWindow::on_actionUser_defined_triggered()
{
    userDefineWindows = new Dialog(this);
    userDefineWindows->show();
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox message(QMessageBox::NoIcon,tr("Help"),tr("Click whatever you want!!!"));
    message.setIconPixmap(QPixmap("unknow.png"));
    message.exec();
}

void MainWindow::on_actionHow_to_play_triggered()
{
    QMessageBox message(QMessageBox::NoIcon,tr("How to play"),tr("Easy"));
    message.setIconPixmap(QPixmap("baidu.png"));
    message.exec();
}

void MainWindow::on_actionAbout_author_triggered()
{
    QMessageBox message(QMessageBox::NoIcon,tr("Auther"),tr("W J,thank yo play"));
    message.setIconPixmap(QPixmap("agree.png"));
    message.exec();
}
void MainWindow::createinterface(int Row,int Col,int BoomNum)
{
    gameOver = false;
    timeOut =true;
    mine = new Block(Row,Col,BoomNum);
    LENGTH=mine->getcol()*21;
    HEIGHT=mine->getrow()*21 + TITILE_HEIGH;
    app->setMinimumSize(LENGTH,HEIGHT);
    app->setMaximumSize(LENGTH,HEIGHT);
}
