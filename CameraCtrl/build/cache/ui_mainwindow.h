/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "winleft.h"
#include "winright.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    WinLeft *Win_Left;
    WinRight *Win_Right;
    QLabel *Label_Hide_L;
    QLabel *Label_Hide_R;
    QLabel *Buffer_2;
    QLabel *Buffer_1;
    QFrame *frame;
    QFrame *frame_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(491, 417);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("QWidget#Win_Right{\n"
"	border-image: url(:/image/background/mainwin.png);\n"
"}\n"
"QWidget#Win_Left{\n"
"	border-image: url(:/image/background/mainwin.png);\n"
"}"));
        Win_Left = new WinLeft(centralwidget);
        Win_Left->setObjectName(QString::fromUtf8("Win_Left"));
        Win_Left->setGeometry(QRect(0, 0, 268, 417));
        Win_Right = new WinRight(centralwidget);
        Win_Right->setObjectName(QString::fromUtf8("Win_Right"));
        Win_Right->setGeometry(QRect(267, 0, 224, 417));
        Win_Right->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color: rgb(116, 114, 114);\n"
"	background-color: rgb(39, 39, 39);\n"
"	border:1px solid #424242;\n"
"	border-radius:1px;\n"
"	\n"
"	border-bottom:1px solid rgb(27, 27, 27);\n"
"	border-right:2px solid #1c1c1c;\n"
"}\n"
"QPushButton:checked{\n"
"color: rgb(226, 222, 222);\n"
"background-color: rgb(65, 65, 65);\n"
"}\n"
"QPushButton::hover{\n"
"	background-color: rgb(54, 54, 54);\n"
"}\n"
"\n"
"QLine{\n"
"	background-color: rgb(154, 154, 154);\n"
"}\n"
"\n"
"/*-------------------------\346\273\221\345\212\250\346\235\241\351\203\250\345\210\206--------------------*/\n"
"QSlider::groove:horizontal{\n"
"	border: 1px;\n"
"	height: 3px; \n"
"	position: absolute;\n"
"	border-radius :1px;\n"
"	margin: 1px 0;\n"
"	left: 2px; right: 2px;\n"
"	background-color: rgb(164, 164, 164);\n"
"}\n"
"/*\346\273\221\345\212\250\346\211\213\346\237\204\351\203\250\345\210\206*/\n"
"QSlider::handle:horizontal:enabled{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a4c4f8, stop:1 #68a3ed);\n"
"    "
                        "border: 1px;\n"
"    width: 15px;\n"
"    height: 10px;\n"
"    margin: -4px -1;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:!enabled{\n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #bfbfbf);\n"
"    border: 1px;\n"
"    width: 15px;\n"
"    height: 10px;\n"
"    margin: -4px -1;\n"
"    border-radius: 5px;\n"
"}\n"
""));
        Label_Hide_L = new QLabel(centralwidget);
        Label_Hide_L->setObjectName(QString::fromUtf8("Label_Hide_L"));
        Label_Hide_L->setGeometry(QRect(0, 0, 10, 417));
        Label_Hide_L->setStyleSheet(QString::fromUtf8("border-image: url(:/image/icon/Hide_line.png);\n"
""));
        Label_Hide_R = new QLabel(centralwidget);
        Label_Hide_R->setObjectName(QString::fromUtf8("Label_Hide_R"));
        Label_Hide_R->setGeometry(QRect(267, 0, 10, 417));
        Label_Hide_R->setStyleSheet(QString::fromUtf8("border-image: url(:/image/icon/Hide_line.png);\n"
"\n"
""));
        Buffer_2 = new QLabel(centralwidget);
        Buffer_2->setObjectName(QString::fromUtf8("Buffer_2"));
        Buffer_2->setGeometry(QRect(267, 224, 46, 417));
        Buffer_1 = new QLabel(centralwidget);
        Buffer_1->setObjectName(QString::fromUtf8("Buffer_1"));
        Buffer_1->setGeometry(QRect(0, 0, 223, 417));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 268, 417));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/image/background/mainwin.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(268, 0, 224, 417));
        frame_2->setStyleSheet(QString::fromUtf8("border-image: url(:/image/background/mainwin.png);"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        MainWindow->setCentralWidget(centralwidget);
        frame_2->raise();
        frame->raise();
        Buffer_1->raise();
        Buffer_2->raise();
        Win_Left->raise();
        Win_Right->raise();
        Label_Hide_R->raise();
        Label_Hide_L->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Label_Hide_L->setText(QString());
        Label_Hide_R->setText(QString());
        Buffer_2->setText(QString());
        Buffer_1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
