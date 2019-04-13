#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QMessageBox>

class Dialog : public QDialog
{
    Q_OBJECT
public:
    Dialog(QWidget* parent = 0);
    ~Dialog();
private:
    QLabel* labelRow,*labelCol,*labelBoomNum;
    QLineEdit* editRow,*editCol,*editBoomNum;
    QPushButton* button;
//    MainWindow mainWindow;
    int Row, Col, BoomNum;
//    int getcol(int col);
//    int getrowCol(int row);
//    int getBoomNum(int boomnum);
//    void change_Row_Col_BoomNum(int row,int col,int boomnum);
//    void interface(MainWindow* mainWindow);
private slots:
    void getRowCol();
};

#endif // DIALOG_H
