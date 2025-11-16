/********************************************************************************
** Form generated from reading UI file 'winleft.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINLEFT_H
#define UI_WINLEFT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinLeft
{
public:
    QFrame *line_3;
    QLabel *label_7;
    QLabel *label_10;
    QSlider *Slider_Gamma;
    QSlider *Slider_Hue;
    QSlider *Slider_WB;
    QLabel *label_11;
    QSlider *Slider_Contrast;
    QLabel *label_14;
    QSlider *Slider_Brightness;
    QLabel *label_15;
    QSlider *Slider_Saturation;
    QLabel *label_18;
    QSlider *Slider_Sharpness;
    QLabel *label_19;
    QFrame *line_2;
    QLabel *label_25;
    QComboBox *ComboBox_Flicker;
    QPushButton *BT_Mirror;
    QPushButton *BT_Flip;
    QPushButton *BT_HOME;
    QPushButton *BT_Menu;
    QPushButton *BT_Reset;
    QFrame *line_11;
    QPushButton *BT_PUSH;
    QPushButton *BT_AI;
    QLineEdit *v_brightness;
    QLineEdit *v_contrast;
    QLineEdit *v_hue;
    QLineEdit *v_saturation;
    QLineEdit *v_sharpness;
    QLineEdit *v_gamma;
    QLineEdit *v_wb;
    QSlider *Slider_BLC;
    QLineEdit *v_blc;
    QLabel *label_12;
    QLabel *label_13;
    QCheckBox *Cb_WB;
    QPushButton *BT_IR;
    QPushButton *BT_DAY;
    QPushButton *BT_RST_PTZ;

    void setupUi(QWidget *WinLeft)
    {
        if (WinLeft->objectName().isEmpty())
            WinLeft->setObjectName(QString::fromUtf8("WinLeft"));
        WinLeft->resize(267, 417);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        WinLeft->setFont(font);
        WinLeft->setStyleSheet(QString::fromUtf8("QWidget#WinLeft{\n"
"	border-image: url(:/image/background/mainwin.png);\n"
"}\n"
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
"    border: 1px;\n"
"    width: 15px;\n"
"    height: 10px;\n"
"    margin: -4px -1;\n"
"    border-radius: 5px;\n"
"}\n"
"QSlider::handle:horizontal:!enabled{\n"
"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #cccccc, stop:1 #bfbfbf);\n"
"    border: 1px;\n"
"    width: 15px;\n"
"    height: 10px;\n"
"    margin: -4px -1;\n"
"    border-radius: 5px;\n"
"}\n"
"QLabel{\n"
"	color: rgb(2"
                        "26, 222, 222);\n"
"}\n"
"\n"
"\n"
"/*\346\214\211\351\222\256\351\203\250\345\210\206*/\n"
"QPushButton:enabled{\n"
"	background-color: rgb(67, 67, 67);\n"
"	color: rgb(226, 222, 222);\n"
"	border:1px solid #5a5a5a;\n"
"}\n"
"QPushButton:!enabled{\n"
"	background-color: rgb(88, 88, 88);\n"
"	color: rgb(226, 222, 222);\n"
"	border:1px solid #5a5a5a;\n"
"}\n"
"QPushButton:checked{\n"
"	color: rgb(236, 236, 236);\n"
"background-color: rgb(54, 54, 54);\n"
"\n"
"}\n"
"QPushButton::hover{\n"
"	background-color: rgb(54, 54, 54);\n"
"}\n"
"QLine{\n"
"	background-color: rgb(154, 154, 154);\n"
"}"));
        line_3 = new QFrame(WinLeft);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(210, 0, 1, 417));
        line_3->setStyleSheet(QString::fromUtf8("	background-color: rgb(154, 154, 154);\n"
""));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(WinLeft);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(5, 100, 66, 20));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setStyleStrategy(QFont::PreferDefault);
        label_7->setFont(font1);
        label_10 = new QLabel(WinLeft);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(5, 220, 66, 20));
        label_10->setFont(font1);
        Slider_Gamma = new QSlider(WinLeft);
        Slider_Gamma->setObjectName(QString::fromUtf8("Slider_Gamma"));
        Slider_Gamma->setGeometry(QRect(70, 220, 92, 16));
        Slider_Gamma->setMaximum(20);
        Slider_Gamma->setPageStep(1);
        Slider_Gamma->setValue(0);
        Slider_Gamma->setOrientation(Qt::Horizontal);
        Slider_Hue = new QSlider(WinLeft);
        Slider_Hue->setObjectName(QString::fromUtf8("Slider_Hue"));
        Slider_Hue->setGeometry(QRect(70, 100, 92, 16));
        Slider_Hue->setMaximum(20);
        Slider_Hue->setPageStep(1);
        Slider_Hue->setValue(0);
        Slider_Hue->setOrientation(Qt::Horizontal);
        Slider_WB = new QSlider(WinLeft);
        Slider_WB->setObjectName(QString::fromUtf8("Slider_WB"));
        Slider_WB->setGeometry(QRect(30, 340, 131, 16));
        Slider_WB->setMaximum(20);
        Slider_WB->setPageStep(1);
        Slider_WB->setValue(0);
        Slider_WB->setOrientation(Qt::Horizontal);
        label_11 = new QLabel(WinLeft);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(5, 300, 91, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setWeight(50);
        font2.setStyleStrategy(QFont::PreferDefault);
        label_11->setFont(font2);
        Slider_Contrast = new QSlider(WinLeft);
        Slider_Contrast->setObjectName(QString::fromUtf8("Slider_Contrast"));
        Slider_Contrast->setGeometry(QRect(70, 60, 92, 16));
        Slider_Contrast->setMaximum(20);
        Slider_Contrast->setPageStep(1);
        Slider_Contrast->setValue(0);
        Slider_Contrast->setOrientation(Qt::Horizontal);
        label_14 = new QLabel(WinLeft);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(5, 60, 66, 20));
        label_14->setFont(font1);
        Slider_Brightness = new QSlider(WinLeft);
        Slider_Brightness->setObjectName(QString::fromUtf8("Slider_Brightness"));
        Slider_Brightness->setGeometry(QRect(70, 20, 92, 16));
        Slider_Brightness->setMaximum(20);
        Slider_Brightness->setPageStep(1);
        Slider_Brightness->setValue(0);
        Slider_Brightness->setOrientation(Qt::Horizontal);
        label_15 = new QLabel(WinLeft);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(5, 20, 66, 20));
        label_15->setFont(font1);
        Slider_Saturation = new QSlider(WinLeft);
        Slider_Saturation->setObjectName(QString::fromUtf8("Slider_Saturation"));
        Slider_Saturation->setGeometry(QRect(70, 140, 92, 16));
        Slider_Saturation->setMaximum(20);
        Slider_Saturation->setPageStep(1);
        Slider_Saturation->setValue(0);
        Slider_Saturation->setOrientation(Qt::Horizontal);
        label_18 = new QLabel(WinLeft);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(5, 140, 66, 20));
        label_18->setFont(font1);
        Slider_Sharpness = new QSlider(WinLeft);
        Slider_Sharpness->setObjectName(QString::fromUtf8("Slider_Sharpness"));
        Slider_Sharpness->setGeometry(QRect(70, 180, 92, 16));
        Slider_Sharpness->setMaximum(20);
        Slider_Sharpness->setPageStep(1);
        Slider_Sharpness->setValue(0);
        Slider_Sharpness->setOrientation(Qt::Horizontal);
        label_19 = new QLabel(WinLeft);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(5, 180, 66, 20));
        label_19->setFont(font1);
        line_2 = new QFrame(WinLeft);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 380, 200, 1));
        line_2->setStyleSheet(QString::fromUtf8("	background-color: rgb(154, 154, 154);\n"
""));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_25 = new QLabel(WinLeft);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(25, 388, 66, 20));
        label_25->setFont(font1);
        ComboBox_Flicker = new QComboBox(WinLeft);
        ComboBox_Flicker->addItem(QString());
        ComboBox_Flicker->addItem(QString());
        ComboBox_Flicker->addItem(QString());
        ComboBox_Flicker->setObjectName(QString::fromUtf8("ComboBox_Flicker"));
        ComboBox_Flicker->setGeometry(QRect(75, 391, 55, 16));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(8);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        ComboBox_Flicker->setFont(font3);
        ComboBox_Flicker->setFocusPolicy(Qt::WheelFocus);
        ComboBox_Flicker->setStyleSheet(QString::fromUtf8("QComboBox{\n"
"	border:0px;\n"
"	border-radius:4px;\n"
"	color: rgb(112, 112, 112);\n"
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
        BT_Mirror = new QPushButton(WinLeft);
        BT_Mirror->setObjectName(QString::fromUtf8("BT_Mirror"));
        BT_Mirror->setGeometry(QRect(215, 140, 48, 25));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Arial"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setWeight(50);
        BT_Mirror->setFont(font4);
        BT_Mirror->setCheckable(false);
        BT_Flip = new QPushButton(WinLeft);
        BT_Flip->setObjectName(QString::fromUtf8("BT_Flip"));
        BT_Flip->setGeometry(QRect(215, 100, 48, 25));
        BT_Flip->setFont(font4);
        BT_Flip->setCheckable(false);
        BT_HOME = new QPushButton(WinLeft);
        BT_HOME->setObjectName(QString::fromUtf8("BT_HOME"));
        BT_HOME->setGeometry(QRect(215, 220, 48, 25));
        BT_HOME->setFont(font4);
        BT_HOME->setCheckable(false);
        BT_Menu = new QPushButton(WinLeft);
        BT_Menu->setObjectName(QString::fromUtf8("BT_Menu"));
        BT_Menu->setGeometry(QRect(215, 180, 48, 25));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Arial"));
        font5.setPointSize(7);
        font5.setBold(false);
        font5.setWeight(50);
        BT_Menu->setFont(font5);
        BT_Menu->setContextMenuPolicy(Qt::CustomContextMenu);
        BT_Menu->setCheckable(false);
        BT_Reset = new QPushButton(WinLeft);
        BT_Reset->setObjectName(QString::fromUtf8("BT_Reset"));
        BT_Reset->setGeometry(QRect(215, 340, 48, 25));
        BT_Reset->setFont(font4);
        BT_Reset->setCheckable(false);
        line_11 = new QFrame(WinLeft);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setGeometry(QRect(267, 0, 1, 417));
        line_11->setStyleSheet(QString::fromUtf8("	background-color: rgb(154, 154, 154);\n"
""));
        line_11->setFrameShape(QFrame::VLine);
        line_11->setFrameShadow(QFrame::Sunken);
        BT_PUSH = new QPushButton(WinLeft);
        BT_PUSH->setObjectName(QString::fromUtf8("BT_PUSH"));
        BT_PUSH->setGeometry(QRect(215, 300, 48, 25));
        BT_PUSH->setFont(font4);
        BT_PUSH->setCheckable(false);
        BT_AI = new QPushButton(WinLeft);
        BT_AI->setObjectName(QString::fromUtf8("BT_AI"));
        BT_AI->setGeometry(QRect(215, 260, 48, 25));
        BT_AI->setFont(font4);
        BT_AI->setCheckable(false);
        v_brightness = new QLineEdit(WinLeft);
        v_brightness->setObjectName(QString::fromUtf8("v_brightness"));
        v_brightness->setGeometry(QRect(165, 20, 40, 20));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Arial"));
        v_brightness->setFont(font6);
        v_brightness->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(255, 255, 255);\n"
"border-radius:3px;qproperty-alignment:AlignHCenter;"));
        v_brightness->setReadOnly(true);
        v_contrast = new QLineEdit(WinLeft);
        v_contrast->setObjectName(QString::fromUtf8("v_contrast"));
        v_contrast->setGeometry(QRect(165, 60, 40, 20));
        v_contrast->setFont(font6);
        v_contrast->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(255, 255, 255);\n"
"border-radius:3px;qproperty-alignment:AlignHCenter;"));
        v_contrast->setReadOnly(true);
        v_hue = new QLineEdit(WinLeft);
        v_hue->setObjectName(QString::fromUtf8("v_hue"));
        v_hue->setGeometry(QRect(165, 100, 40, 20));
        v_hue->setFont(font6);
        v_hue->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(255, 255, 255);\n"
"border-radius:3px;qproperty-alignment:AlignHCenter;"));
        v_hue->setReadOnly(true);
        v_saturation = new QLineEdit(WinLeft);
        v_saturation->setObjectName(QString::fromUtf8("v_saturation"));
        v_saturation->setGeometry(QRect(165, 140, 40, 20));
        v_saturation->setFont(font6);
        v_saturation->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(255, 255, 255);\n"
"border-radius:3px;qproperty-alignment:AlignHCenter;"));
        v_saturation->setReadOnly(true);
        v_sharpness = new QLineEdit(WinLeft);
        v_sharpness->setObjectName(QString::fromUtf8("v_sharpness"));
        v_sharpness->setGeometry(QRect(165, 180, 40, 20));
        v_sharpness->setFont(font6);
        v_sharpness->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(255, 255, 255);\n"
"border-radius:3px;qproperty-alignment:AlignHCenter;"));
        v_sharpness->setReadOnly(true);
        v_gamma = new QLineEdit(WinLeft);
        v_gamma->setObjectName(QString::fromUtf8("v_gamma"));
        v_gamma->setGeometry(QRect(165, 220, 40, 20));
        v_gamma->setFont(font6);
        v_gamma->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(255, 255, 255);\n"
"border-radius:3px;qproperty-alignment:AlignHCenter;"));
        v_gamma->setReadOnly(true);
        v_wb = new QLineEdit(WinLeft);
        v_wb->setObjectName(QString::fromUtf8("v_wb"));
        v_wb->setGeometry(QRect(165, 340, 40, 20));
        v_wb->setFont(font6);
        v_wb->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(255, 255, 255);\n"
"border-radius:3px;qproperty-alignment:AlignHCenter;"));
        v_wb->setReadOnly(true);
        Slider_BLC = new QSlider(WinLeft);
        Slider_BLC->setObjectName(QString::fromUtf8("Slider_BLC"));
        Slider_BLC->setGeometry(QRect(70, 260, 92, 16));
        Slider_BLC->setMaximum(20);
        Slider_BLC->setPageStep(1);
        Slider_BLC->setValue(0);
        Slider_BLC->setOrientation(Qt::Horizontal);
        v_blc = new QLineEdit(WinLeft);
        v_blc->setObjectName(QString::fromUtf8("v_blc"));
        v_blc->setGeometry(QRect(165, 260, 40, 20));
        v_blc->setFont(font6);
        v_blc->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"color: rgb(255, 255, 255);\n"
"border-radius:3px;qproperty-alignment:AlignHCenter;"));
        v_blc->setReadOnly(true);
        label_12 = new QLabel(WinLeft);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(5, 260, 66, 20));
        label_12->setFont(font1);
        label_13 = new QLabel(WinLeft);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(140, 300, 31, 20));
        label_13->setFont(font2);
        Cb_WB = new QCheckBox(WinLeft);
        Cb_WB->setObjectName(QString::fromUtf8("Cb_WB"));
        Cb_WB->setGeometry(QRect(178, 303, 16, 16));
        BT_IR = new QPushButton(WinLeft);
        BT_IR->setObjectName(QString::fromUtf8("BT_IR"));
        BT_IR->setGeometry(QRect(215, 20, 48, 25));
        BT_IR->setFont(font4);
        BT_IR->setCheckable(false);
        BT_DAY = new QPushButton(WinLeft);
        BT_DAY->setObjectName(QString::fromUtf8("BT_DAY"));
        BT_DAY->setGeometry(QRect(215, 60, 48, 25));
        BT_DAY->setFont(font4);
        BT_DAY->setCheckable(false);
        BT_RST_PTZ = new QPushButton(WinLeft);
        BT_RST_PTZ->setObjectName(QString::fromUtf8("BT_RST_PTZ"));
        BT_RST_PTZ->setGeometry(QRect(215, 380, 48, 25));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Arial"));
        font7.setPointSize(8);
        font7.setBold(false);
        font7.setWeight(50);
        BT_RST_PTZ->setFont(font7);
        BT_RST_PTZ->setCheckable(false);

        retranslateUi(WinLeft);

        ComboBox_Flicker->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(WinLeft);
    } // setupUi

    void retranslateUi(QWidget *WinLeft)
    {
        WinLeft->setWindowTitle(QCoreApplication::translate("WinLeft", "Form", nullptr));
        label_7->setText(QCoreApplication::translate("WinLeft", "Hue", nullptr));
        label_10->setText(QCoreApplication::translate("WinLeft", "Gamma", nullptr));
        label_11->setText(QCoreApplication::translate("WinLeft", "WhiteBalance", nullptr));
        label_14->setText(QCoreApplication::translate("WinLeft", "Contrast", nullptr));
        label_15->setText(QCoreApplication::translate("WinLeft", "Brightness", nullptr));
        label_18->setText(QCoreApplication::translate("WinLeft", "Saturation", nullptr));
        label_19->setText(QCoreApplication::translate("WinLeft", "Sharpness", nullptr));
        label_25->setText(QCoreApplication::translate("WinLeft", "Flicker", nullptr));
        ComboBox_Flicker->setItemText(0, QCoreApplication::translate("WinLeft", "OFF", nullptr));
        ComboBox_Flicker->setItemText(1, QCoreApplication::translate("WinLeft", "50Hz", nullptr));
        ComboBox_Flicker->setItemText(2, QCoreApplication::translate("WinLeft", "60Hz", nullptr));

        BT_Mirror->setText(QCoreApplication::translate("WinLeft", "Mirror", nullptr));
        BT_Flip->setText(QCoreApplication::translate("WinLeft", "Flip", nullptr));
        BT_HOME->setText(QCoreApplication::translate("WinLeft", "Home", nullptr));
        BT_Menu->setText(QCoreApplication::translate("WinLeft", "Menu OFF", nullptr));
        BT_Reset->setText(QCoreApplication::translate("WinLeft", "Reset", nullptr));
        BT_PUSH->setText(QCoreApplication::translate("WinLeft", "Push", nullptr));
        BT_AI->setText(QCoreApplication::translate("WinLeft", "Framing", nullptr));
        v_brightness->setText(QCoreApplication::translate("WinLeft", "10000", nullptr));
        v_contrast->setText(QCoreApplication::translate("WinLeft", "10000", nullptr));
        v_hue->setText(QCoreApplication::translate("WinLeft", "1000", nullptr));
        v_saturation->setText(QCoreApplication::translate("WinLeft", "1000", nullptr));
        v_sharpness->setText(QCoreApplication::translate("WinLeft", "1000", nullptr));
        v_gamma->setText(QCoreApplication::translate("WinLeft", "1000", nullptr));
        v_wb->setText(QCoreApplication::translate("WinLeft", "1000", nullptr));
        v_blc->setText(QCoreApplication::translate("WinLeft", "1000", nullptr));
        label_12->setText(QCoreApplication::translate("WinLeft", "BackLight", nullptr));
        label_13->setText(QCoreApplication::translate("WinLeft", "Auto", nullptr));
        Cb_WB->setText(QString());
        BT_IR->setText(QCoreApplication::translate("WinLeft", "IR OFF", nullptr));
        BT_DAY->setText(QCoreApplication::translate("WinLeft", "DAY", nullptr));
        BT_RST_PTZ->setText(QCoreApplication::translate("WinLeft", "RST-PTZ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WinLeft: public Ui_WinLeft {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINLEFT_H
