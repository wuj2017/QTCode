/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionprimary;
    QAction *actionMiddle;
    QAction *actionSenor;
    QAction *actionUser_defined;
    QAction *actionQuit;
    QAction *actionHelp;
    QAction *actionHow_to_play;
    QAction *actionAbout_author;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuGame;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        actionprimary = new QAction(MainWindow);
        actionprimary->setObjectName(QStringLiteral("actionprimary"));
        actionMiddle = new QAction(MainWindow);
        actionMiddle->setObjectName(QStringLiteral("actionMiddle"));
        actionSenor = new QAction(MainWindow);
        actionSenor->setObjectName(QStringLiteral("actionSenor"));
        actionUser_defined = new QAction(MainWindow);
        actionUser_defined->setObjectName(QStringLiteral("actionUser_defined"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionHow_to_play = new QAction(MainWindow);
        actionHow_to_play->setObjectName(QStringLiteral("actionHow_to_play"));
        actionAbout_author = new QAction(MainWindow);
        actionAbout_author->setObjectName(QStringLiteral("actionAbout_author"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 26));
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QStringLiteral("menuGame"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuGame->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuGame->addAction(actionprimary);
        menuGame->addAction(actionMiddle);
        menuGame->addAction(actionSenor);
        menuGame->addAction(actionUser_defined);
        menuGame->addAction(actionQuit);
        menuHelp->addAction(actionHelp);
        menuHelp->addAction(actionHow_to_play);
        menuHelp->addAction(actionAbout_author);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionprimary->setText(QApplication::translate("MainWindow", "Primary", Q_NULLPTR));
        actionMiddle->setText(QApplication::translate("MainWindow", "Middle", Q_NULLPTR));
        actionSenor->setText(QApplication::translate("MainWindow", "Senior", Q_NULLPTR));
        actionUser_defined->setText(QApplication::translate("MainWindow", "User-defined", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        actionHow_to_play->setText(QApplication::translate("MainWindow", "How to play", Q_NULLPTR));
        actionAbout_author->setText(QApplication::translate("MainWindow", "About author", Q_NULLPTR));
        menuGame->setTitle(QApplication::translate("MainWindow", "Game", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "About", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
