/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tetris
{
public:
    QWidget *centralwidget;
    QFrame *grid;
    QFrame *nextpiece;
    QFrame *next3pieces;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Tetris)
    {
        if (Tetris->objectName().isEmpty())
            Tetris->setObjectName("Tetris");
        Tetris->resize(412, 430);
        centralwidget = new QWidget(Tetris);
        centralwidget->setObjectName("centralwidget");
        grid = new QFrame(centralwidget);
        grid->setObjectName("grid");
        grid->setGeometry(QRect(30, 20, 231, 361));
        grid->setFrameShape(QFrame::Shape::StyledPanel);
        grid->setFrameShadow(QFrame::Shadow::Raised);
        nextpiece = new QFrame(centralwidget);
        nextpiece->setObjectName("nextpiece");
        nextpiece->setGeometry(QRect(300, 30, 91, 80));
        nextpiece->setFrameShape(QFrame::Shape::StyledPanel);
        nextpiece->setFrameShadow(QFrame::Shadow::Raised);
        next3pieces = new QFrame(centralwidget);
        next3pieces->setObjectName("next3pieces");
        next3pieces->setGeometry(QRect(310, 110, 71, 201));
        next3pieces->setFrameShape(QFrame::Shape::StyledPanel);
        next3pieces->setFrameShadow(QFrame::Shadow::Raised);
        Tetris->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Tetris);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 412, 37));
        Tetris->setMenuBar(menubar);
        statusbar = new QStatusBar(Tetris);
        statusbar->setObjectName("statusbar");
        Tetris->setStatusBar(statusbar);

        retranslateUi(Tetris);

        QMetaObject::connectSlotsByName(Tetris);
    } // setupUi

    void retranslateUi(QMainWindow *Tetris)
    {
        Tetris->setWindowTitle(QCoreApplication::translate("Tetris", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tetris: public Ui_Tetris {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
