#include "dialog.h"
#include "mainwindow.h"

Dialog::Dialog(QWidget* parent)
    :QDialog(parent)
{
    labelRow = new QLabel(this);
    labelRow->setText(tr("Input Row"));
    labelCol = new QLabel(this);
    labelCol->setText(tr("Input Col"));
    labelBoomNum = new QLabel(this);
    labelBoomNum->setText(tr("Boom Num"));
    editRow = new QLineEdit(this);
    editCol = new QLineEdit(this);
    editBoomNum =new QLineEdit(this);
    button = new QPushButton(this);
    button->setText(tr("Apply"));
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(labelRow,0,0);
    layout->addWidget(labelCol,1,0);
    layout->addWidget(labelBoomNum,2,0);
    layout->addWidget(editRow,0,1);
    layout->addWidget(editCol,1,1);
    layout->addWidget(editBoomNum,2,1);
    layout->addWidget(button,3,1);
//    connect(button,SIGNAL(clicked()),this,SLOT(getRowCol()));
    connect(button,&QPushButton::clicked,this,&Dialog::getRowCol);
}
void Dialog::getRowCol()
{
    QString str;
    bool ok;
    str = editRow->text();
    this->Row = str.toInt(&ok);
    str = editCol->text();
    this->Col = str.toInt(&ok);
    str = editBoomNum->text();
    this->BoomNum = str.toInt(&ok);
    if(this->Row<9 && this->Col<9)
    {
      QMessageBox message(QMessageBox::NoIcon, "Too low", "You still want to set up more simple than the primary? I will shoot without changing the high point.");
      message.setIconPixmap(QPixmap("low.png"));
      message.exec();
    }
    else
    {
        MainWindow::createinterface(this->Row,this->Col,this->BoomNum);
        this->close();
    }
}
//void Dialog::change_Row_Col_BoomNum(int row, int col, int boomnum)
//{
//    this->Row = row;
//    this->Col = col;
//    this->BoomNum =boomnum;
//}
//void Dialog::interface(MainWindow *mainWindow)
//{

//}

Dialog::~Dialog()
{

}
