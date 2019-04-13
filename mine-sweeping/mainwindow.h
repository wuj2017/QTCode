#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QDialog>
#include "dialog.h"
#include <block.h>


//定义常量
#define BLOCK_LENGTH 21
#define BLOCK_HEIGH 21
#define ELENUM_LENGHT 20
#define EXPRESSION_LENGHT 24                //表情宽度
#define EXPRESSION_HEIGH 24                 //表情长度
#define TTILE_BEGIN 23
#define TITILE_HEIGH  (TTILE_BEGIN+40)
#define PRIMARY_LENGTH  189
#define MIDDLE_LENGTH   336
#define TOP_LENGTH      630


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static void createinterface(int Row,int Col,int BoomNum);

protected:

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_secondadd();

    void on_actionprimary_triggered();
    void on_actionMiddle_triggered();
    void on_actionSenor_triggered();
    void on_actionUser_defined_triggered();
    void on_actionQuit_triggered();
    void on_actionHelp_triggered();
    void on_actionHow_to_play_triggered();
    void on_actionAbout_author_triggered();

private:
    Ui::MainWindow *ui;
    QTimer* runtime;
    Dialog* userDefineWindows;
};


void restart(int row,int col,int boomnum);
void painttitle(QPainter* painter);
void paintboom(QPainter* painter);
void showblock(int x,int y);
bool isWin();
#endif // MAINWINDOW_H
