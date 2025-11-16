/********************************************************************************
** Form generated from reading UI file 'winright.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINRIGHT_H
#define UI_WINRIGHT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "rockerhandle.h"

QT_BEGIN_NAMESPACE

class Ui_WinRight
{
public:
    QPushButton *BT_Close;
    QPushButton *BT_Top;
    QFrame *line;
    QLabel *label;
    QSlider *Slider_Zoom;
    QFrame *line_2;
    QPushButton *BT_0;
    QPushButton *BT_1;
    QPushButton *BT_2;
    QPushButton *BT_5;
    QPushButton *BT_4;
    QPushButton *BT_7;
    QPushButton *BT_8;
    QPushButton *BT_6;
    QPushButton *BT_3;
    QToolButton *toolButton;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_7;
    RockerHandle *widget;
    QToolButton *BT_Set;
    QToolButton *BT_Clear;
    QComboBox *Box_Camera_USB;
    QLabel *label_10;
    QLineEdit *set_pan_data;
    QLineEdit *set_tilt_data;
    QLineEdit *get_pan_data;
    QLineEdit *get_tilt_data;
    QLabel *label_4;
    QLabel *label_9;
    QPushButton *set_pan_tilt;
    QPushButton *get_pan_tilt;
    QLineEdit *get_roll_data;
    QPushButton *get_roll;

    void setupUi(QWidget *WinRight)
    {
        if (WinRight->objectName().isEmpty())
            WinRight->setObjectName(QString::fromUtf8("WinRight"));
        WinRight->resize(224, 417);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setBold(true);
        font.setWeight(75);
        WinRight->setFont(font);
        WinRight->setStyleSheet(QString::fromUtf8("QWidget#WinRight{\n"
"	border-image: url(:/image/background/mainwin.png);\n"
"}\n"
"QPushButton:enabled{\n"
"	color: rgb(116, 114, 114);\n"
"	background-color: rgb(39, 39, 39);\n"
"	border:1px solid #424242;\n"
"	border-radius:1px;\n"
"	border-bottom:1px solid rgb(27, 27, 27);\n"
"	border-right:2px solid #1c1c1c;\n"
"}\n"
"QPushButton:!enabled{\n"
"	background-color: rgb(88, 88, 88);\n"
"}\n"
"\n"
"QPushButton:checked{\n"
"color: rgb(226, 222, 222);\n"
"background-color: rgb(65, 65, 65);\n"
"}\n"
"QPushButton::hover{\n"
"	background-color: rgb(54, 54, 54);\n"
"}\n"
"\n"
"\n"
"\n"
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
"/*\346\273\221\345\212\250\346\211\213"
                        "\346\237\204\351\203\250\345\210\206*/\n"
"QSlider::handle:horizontal:enabled{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a4c4f8, stop:1 #68a3ed);\n"
"    border: 1px;\n"
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
"\n"
""));
        BT_Close = new QPushButton(WinRight);
        BT_Close->setObjectName(QString::fromUtf8("BT_Close"));
        BT_Close->setGeometry(QRect(185, 2, 37, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        BT_Close->setFont(font1);
        BT_Close->setStyleSheet(QString::fromUtf8("border-image: url(:/image/icon/close.png);\n"
"border:0px;"));
        BT_Top = new QPushButton(WinRight);
        BT_Top->setObjectName(QString::fromUtf8("BT_Top"));
        BT_Top->setGeometry(QRect(147, 2, 37, 16));
        BT_Top->setFont(font1);
        BT_Top->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"border-image: url(:/image/icon/arrow_up.png);\n"
"border:0px;\n"
"}\n"
"QPushButton:selected{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/*\n"
"	border:1px solid #424242;\n"
"	border-radius:1px;\n"
"	\n"
"	border-bottom:1px solid rgb(27, 27, 27);\n"
"	border-right:2px solid #1c1c1c;\n"
"**/"));
        BT_Top->setCheckable(true);
        BT_Top->setChecked(true);
        line = new QFrame(WinRight);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(25, 28, 195, 1));
        line->setFont(font1);
        line->setStyleSheet(QString::fromUtf8("	background-color: rgb(154, 154, 154);\n"
""));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(WinRight);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 85, 101, 101));
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/image/icon/position.png);"));
        Slider_Zoom = new QSlider(WinRight);
        Slider_Zoom->setObjectName(QString::fromUtf8("Slider_Zoom"));
        Slider_Zoom->setGeometry(QRect(80, 265, 80, 16));
        Slider_Zoom->setMaximum(14);
        Slider_Zoom->setSingleStep(0);
        Slider_Zoom->setPageStep(0);
        Slider_Zoom->setValue(7);
        Slider_Zoom->setOrientation(Qt::Horizontal);
        line_2 = new QFrame(WinRight);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(22, 290, 195, 1));
        line_2->setFont(font1);
        line_2->setStyleSheet(QString::fromUtf8("	background-color: rgb(154, 154, 154);\n"
""));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        BT_0 = new QPushButton(WinRight);
        BT_0->setObjectName(QString::fromUtf8("BT_0"));
        BT_0->setGeometry(QRect(30, 330, 58, 27));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(11);
        font2.setBold(false);
        font2.setWeight(50);
        BT_0->setFont(font2);
        BT_0->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        BT_0->setCheckable(false);
        BT_1 = new QPushButton(WinRight);
        BT_1->setObjectName(QString::fromUtf8("BT_1"));
        BT_1->setEnabled(true);
        BT_1->setGeometry(QRect(90, 330, 58, 27));
        BT_1->setFont(font2);
        BT_1->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        BT_1->setCheckable(false);
        BT_2 = new QPushButton(WinRight);
        BT_2->setObjectName(QString::fromUtf8("BT_2"));
        BT_2->setGeometry(QRect(150, 330, 58, 27));
        BT_2->setFont(font2);
        BT_2->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        BT_2->setCheckable(false);
        BT_5 = new QPushButton(WinRight);
        BT_5->setObjectName(QString::fromUtf8("BT_5"));
        BT_5->setGeometry(QRect(150, 360, 58, 27));
        BT_5->setFont(font2);
        BT_5->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        BT_5->setCheckable(false);
        BT_4 = new QPushButton(WinRight);
        BT_4->setObjectName(QString::fromUtf8("BT_4"));
        BT_4->setGeometry(QRect(90, 360, 58, 27));
        BT_4->setFont(font2);
        BT_4->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        BT_4->setCheckable(false);
        BT_7 = new QPushButton(WinRight);
        BT_7->setObjectName(QString::fromUtf8("BT_7"));
        BT_7->setGeometry(QRect(90, 390, 58, 27));
        BT_7->setFont(font2);
        BT_7->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        BT_7->setCheckable(false);
        BT_8 = new QPushButton(WinRight);
        BT_8->setObjectName(QString::fromUtf8("BT_8"));
        BT_8->setGeometry(QRect(150, 390, 58, 27));
        BT_8->setFont(font2);
        BT_8->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        BT_8->setCheckable(false);
        BT_6 = new QPushButton(WinRight);
        BT_6->setObjectName(QString::fromUtf8("BT_6"));
        BT_6->setGeometry(QRect(30, 390, 58, 27));
        BT_6->setFont(font2);
        BT_6->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        BT_6->setCheckable(false);
        BT_3 = new QPushButton(WinRight);
        BT_3->setObjectName(QString::fromUtf8("BT_3"));
        BT_3->setGeometry(QRect(30, 360, 58, 27));
        BT_3->setFont(font2);
        BT_3->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        BT_3->setCheckable(false);
        toolButton = new QToolButton(WinRight);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(-5, 0, 30, 417));
        toolButton->setStyleSheet(QString::fromUtf8("border:0px;\n"
"border-image: url(:/image/icon/line.png);"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/icon/arrow_left.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(20, 20));
        toolButton->setCheckable(false);
        label_2 = new QLabel(WinRight);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 265, 16, 16));
        label_2->setStyleSheet(QString::fromUtf8("image: url(:/image/icon/6.png);"));
        label_3 = new QLabel(WinRight);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 270, 6, 7));
        label_3->setStyleSheet(QString::fromUtf8("image: url(:/image/icon/redue.png);"));
        label_6 = new QLabel(WinRight);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(165, 265, 16, 16));
        label_6->setStyleSheet(QString::fromUtf8("image: url(:/image/icon/6.png);"));
        label_7 = new QLabel(WinRight);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(185, 270, 7, 8));
        label_7->setStyleSheet(QString::fromUtf8("image: url(:/image/icon/add.png);"));
        widget = new RockerHandle(WinRight);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(70, 85, 100, 100));
        widget->setStyleSheet(QString::fromUtf8("border-radius:40px;"));
        BT_Set = new QToolButton(WinRight);
        BT_Set->setObjectName(QString::fromUtf8("BT_Set"));
        BT_Set->setGeometry(QRect(30, 300, 75, 27));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(11);
        BT_Set->setFont(font3);
        BT_Set->setStyleSheet(QString::fromUtf8("QToolButton:enabled{\n"
"	color: rgb(226, 222, 222);\n"
"	background-color: rgb(39, 39, 39);\n"
"	border:1px solid #424242;\n"
"	border-radius:1px;\n"
"	border-bottom:1px solid rgb(27, 27, 27);\n"
"	border-right:2px solid #1c1c1c;\n"
"}\n"
"QToolButton:!enabled{\n"
"	color: rgb(226, 222, 222);\n"
"	background-color: rgb(88, 88, 88);\n"
"	border:1px solid #424242;\n"
"	border-radius:1px;\n"
"	border-bottom:1px solid rgb(27, 27, 27);\n"
"	border-right:2px solid #1c1c1c;\n"
"}\n"
"\n"
"QToolButton:checked{\n"
"background-color: rgb(110, 110, 110);\n"
"}\n"
"QToolButton:!checked{\n"
"background-color: rgb(65, 65, 65);\n"
"}\n"
"QToolButton:hover{\n"
"	background-color: rgb(110, 110, 110);\n"
"}\n"
""));
        BT_Set->setCheckable(true);
        BT_Clear = new QToolButton(WinRight);
        BT_Clear->setObjectName(QString::fromUtf8("BT_Clear"));
        BT_Clear->setGeometry(QRect(133, 300, 75, 27));
        BT_Clear->setFont(font3);
        BT_Clear->setStyleSheet(QString::fromUtf8("QToolButton:enabled{\n"
"	color: rgb(226, 222, 222);\n"
"	background-color: rgb(39, 39, 39);\n"
"	border:1px solid #424242;\n"
"	border-radius:1px;\n"
"	border-bottom:1px solid rgb(27, 27, 27);\n"
"	border-right:2px solid #1c1c1c;\n"
"}\n"
"QToolButton:!enabled{\n"
"	color: rgb(226, 222, 222);\n"
"	background-color: rgb(88, 88, 88);\n"
"	border:1px solid #424242;\n"
"	border-radius:1px;\n"
"	border-bottom:1px solid rgb(27, 27, 27);\n"
"	border-right:2px solid #1c1c1c;\n"
"}\n"
"\n"
"QToolButton:checked{\n"
"background-color: rgb(110, 110, 110);\n"
"}\n"
"QToolButton:!checked{\n"
"background-color: rgb(65, 65, 65);\n"
"}\n"
"QToolButton:hover{\n"
"	background-color: rgb(110, 110, 110);\n"
"}\n"
""));
        BT_Clear->setCheckable(true);
        Box_Camera_USB = new QComboBox(WinRight);
        Box_Camera_USB->setObjectName(QString::fromUtf8("Box_Camera_USB"));
        Box_Camera_USB->setGeometry(QRect(70, 40, 140, 16));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Arial"));
        font4.setPointSize(8);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        Box_Camera_USB->setFont(font4);
        Box_Camera_USB->setStyleSheet(QString::fromUtf8("QComboBox{\n"
"	border:0px;\n"
"	border-radius:4px;\n"
"	color: rgb(112, 112, 112);	padding:0 6px;\n"
"\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"      subcontrol-origin: padding;\n"
"      subcontrol-position: top right;\n"
"      width: 20px;\n"
"      border-left-width: 0px;\n"
"      border-left-color: darkgray;\n"
"      border-left-style: solid; /* just a single line */\n"
"      border-top-right-radius: 4px; /* same radius as the QComboBox */\n"
"      border-bottom-right-radius: 4px;\n"
"  }\n"
"QComboBox::down-arrow {\n"
"    \n"
"	border-image: url(:/image/icon/arrow.png);\n"
"}"));
        label_10 = new QLabel(WinRight);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 42, 54, 12));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Arial"));
        label_10->setFont(font5);
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        set_pan_data = new QLineEdit(WinRight);
        set_pan_data->setObjectName(QString::fromUtf8("set_pan_data"));
        set_pan_data->setGeometry(QRect(30, 214, 61, 20));
        set_tilt_data = new QLineEdit(WinRight);
        set_tilt_data->setObjectName(QString::fromUtf8("set_tilt_data"));
        set_tilt_data->setGeometry(QRect(30, 240, 61, 20));
        get_pan_data = new QLineEdit(WinRight);
        get_pan_data->setObjectName(QString::fromUtf8("get_pan_data"));
        get_pan_data->setGeometry(QRect(150, 214, 61, 20));
        get_pan_data->setReadOnly(true);
        get_tilt_data = new QLineEdit(WinRight);
        get_tilt_data->setObjectName(QString::fromUtf8("get_tilt_data"));
        get_tilt_data->setGeometry(QRect(150, 240, 61, 20));
        get_tilt_data->setReadOnly(true);
        label_4 = new QLabel(WinRight);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(110, 214, 31, 16));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_9 = new QLabel(WinRight);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(110, 240, 31, 16));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        set_pan_tilt = new QPushButton(WinRight);
        set_pan_tilt->setObjectName(QString::fromUtf8("set_pan_tilt"));
        set_pan_tilt->setGeometry(QRect(30, 180, 58, 27));
        set_pan_tilt->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        get_pan_tilt = new QPushButton(WinRight);
        get_pan_tilt->setObjectName(QString::fromUtf8("get_pan_tilt"));
        get_pan_tilt->setGeometry(QRect(150, 180, 58, 27));
        get_pan_tilt->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        get_roll_data = new QLineEdit(WinRight);
        get_roll_data->setObjectName(QString::fromUtf8("get_roll_data"));
        get_roll_data->setGeometry(QRect(160, 60, 61, 20));
        get_roll = new QPushButton(WinRight);
        get_roll->setObjectName(QString::fromUtf8("get_roll"));
        get_roll->setGeometry(QRect(10, 60, 58, 27));
        get_roll->setStyleSheet(QString::fromUtf8("color: rgb(226, 222, 222);"));
        label->raise();
        BT_Close->raise();
        BT_Top->raise();
        line->raise();
        Slider_Zoom->raise();
        line_2->raise();
        BT_0->raise();
        BT_1->raise();
        BT_2->raise();
        BT_5->raise();
        BT_4->raise();
        BT_7->raise();
        BT_8->raise();
        BT_6->raise();
        BT_3->raise();
        toolButton->raise();
        label_2->raise();
        label_3->raise();
        label_6->raise();
        label_7->raise();
        widget->raise();
        BT_Set->raise();
        BT_Clear->raise();
        Box_Camera_USB->raise();
        label_10->raise();
        set_pan_data->raise();
        set_tilt_data->raise();
        get_pan_data->raise();
        get_tilt_data->raise();
        label_4->raise();
        label_9->raise();
        set_pan_tilt->raise();
        get_pan_tilt->raise();
        get_roll_data->raise();
        get_roll->raise();

        retranslateUi(WinRight);

        QMetaObject::connectSlotsByName(WinRight);
    } // setupUi

    void retranslateUi(QWidget *WinRight)
    {
        WinRight->setWindowTitle(QCoreApplication::translate("WinRight", "Form", nullptr));
        BT_Close->setText(QString());
        BT_Top->setText(QString());
        label->setText(QString());
        BT_0->setText(QCoreApplication::translate("WinRight", "0", nullptr));
        BT_1->setText(QCoreApplication::translate("WinRight", "1", nullptr));
        BT_2->setText(QCoreApplication::translate("WinRight", "2", nullptr));
        BT_5->setText(QCoreApplication::translate("WinRight", "5", nullptr));
        BT_4->setText(QCoreApplication::translate("WinRight", "4", nullptr));
        BT_7->setText(QCoreApplication::translate("WinRight", "7", nullptr));
        BT_8->setText(QCoreApplication::translate("WinRight", "8", nullptr));
        BT_6->setText(QCoreApplication::translate("WinRight", "6", nullptr));
        BT_3->setText(QCoreApplication::translate("WinRight", "3", nullptr));
        toolButton->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_6->setText(QString());
        label_7->setText(QString());
        BT_Set->setText(QCoreApplication::translate("WinRight", "Set", nullptr));
        BT_Clear->setText(QCoreApplication::translate("WinRight", "Clear", nullptr));
        Box_Camera_USB->setCurrentText(QString());
        label_10->setText(QCoreApplication::translate("WinRight", "Device", nullptr));
        set_pan_data->setText(QCoreApplication::translate("WinRight", "0", nullptr));
        set_tilt_data->setText(QCoreApplication::translate("WinRight", "0", nullptr));
        label_4->setText(QCoreApplication::translate("WinRight", "PAN", nullptr));
        label_9->setText(QCoreApplication::translate("WinRight", "TILT", nullptr));
        set_pan_tilt->setText(QCoreApplication::translate("WinRight", "SET/PT", nullptr));
        get_pan_tilt->setText(QCoreApplication::translate("WinRight", "GET/PT", nullptr));
        get_roll_data->setText(QCoreApplication::translate("WinRight", "0", nullptr));
        get_roll->setText(QCoreApplication::translate("WinRight", "GET ROLL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinRight: public Ui_WinRight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINRIGHT_H
