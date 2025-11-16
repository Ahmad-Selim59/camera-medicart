#include "winright.h"
#include "ui_winright.h"

#include <QScreen>

WinRight::WinRight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinRight)
{
    ui->setupUi(this);
    WinShow = false;
    Set = false;
    Clear = false;
    connect(ui->widget,SIGNAL(keyNumchanged(int)),this,SLOT(TP_key(int)));
    connect(ui->widget,SIGNAL(Speed_Pan(int)),this,SLOT(TP_Pan(int)));
    connect(ui->widget,SIGNAL(Speed_Tilt(int)),this,SLOT(TP_Tilt(int)));

}

WinRight::~WinRight()
{
    delete ui;
}


void WinRight::TP_key(int num){emit keyNumchanged(num);}
void WinRight::TP_Pan(int num){emit Speed_Pan(num);}
void WinRight::TP_Tilt(int num){emit Speed_Tilt(num);}

void WinRight::on_toolButton_clicked()
{
    if(WinShow == false){
        emit BT_Show(true);
        WinShow = true;
        ui->toolButton->setIcon(QIcon(":/image/icon/arrow_right.png"));
    }else if(WinShow == true){
        emit BT_Show(false);
        WinShow = false;
        ui->toolButton->setIcon(QIcon(":/image/icon/arrow_left.png"));
    }
}

void WinRight::on_BT_Close_clicked()
{
    emit BT_Pressed(1);
}

void WinRight::on_BT_Top_toggled(bool checked)
{
    if(checked == true){
        emit BT_Pressed(201);
    }else if(checked == false){
        emit BT_Pressed(202);
    }
}




void WinRight::on_Slider_Zoom_valueChanged(int value)
{
}

void WinRight::on_Slider_Zoom_sliderReleased()
{
    ui->Slider_Zoom->setValue(7);
}

void WinRight::on_BT_1_clicked()
{
    emit ChangePresetno(1);
    if(Set == false && Clear == false){
        emit BT_Pressed(5);
    }else if(Set == true && Clear == false){
        emit BT_Pressed(6);
        ReSetClear();
    }else if(Set == false && Clear == true){
        emit BT_Pressed(7);
        ReSetClear();
    }
}
void WinRight::on_BT_2_clicked()
{
    emit ChangePresetno(2);
    if(Set == false && Clear == false){
        emit BT_Pressed(5);
    }else if(Set == true && Clear == false){
        emit BT_Pressed(6);
        ReSetClear();
    }else if(Set == false && Clear == true){
        emit BT_Pressed(7);
        ReSetClear();
    }
}
void WinRight::on_BT_3_clicked()
{
    emit ChangePresetno(3);
    if(Set == false && Clear == false){
        emit BT_Pressed(5);
    }else if(Set == true && Clear == false){
        emit BT_Pressed(6);
        ReSetClear();
    }else if(Set == false && Clear == true){
        emit BT_Pressed(7);
        ReSetClear();
    }
}
void WinRight::on_BT_4_clicked()
{
    emit ChangePresetno(4);
    if(Set == false && Clear == false){
        emit BT_Pressed(5);
    }else if(Set == true && Clear == false){
        emit BT_Pressed(6);
        ReSetClear();
    }else if(Set == false && Clear == true){
        emit BT_Pressed(7);
        ReSetClear();
    }
}
void WinRight::on_BT_5_clicked()
{
    emit ChangePresetno(5);
    if(Set == false && Clear == false){
        emit BT_Pressed(5);
    }else if(Set == true && Clear == false){
        emit BT_Pressed(6);
        ReSetClear();
    }else if(Set == false && Clear == true){
        emit BT_Pressed(7);
        ReSetClear();
    }
}
void WinRight::on_BT_6_clicked()
{
    emit ChangePresetno(6);
    if(Set == false && Clear == false){
        emit BT_Pressed(5);
    }else if(Set == true && Clear == false){
        emit BT_Pressed(6);
        ReSetClear();
    }else if(Set == false && Clear == true){
        emit BT_Pressed(7);
        ReSetClear();
    }
}
void WinRight::on_BT_7_clicked()
{
    emit ChangePresetno(7);
    if(Set == false && Clear == false){
        emit BT_Pressed(5);
    }else if(Set == true && Clear == false){
        emit BT_Pressed(6);
        ReSetClear();
    }else if(Set == false && Clear == true){
        emit BT_Pressed(7);
        ReSetClear();
    }
}
void WinRight::on_BT_8_clicked()
{
    emit ChangePresetno(8);
    if(Set == false && Clear == false){
        emit BT_Pressed(5);
    }else if(Set == true && Clear == false){
        emit BT_Pressed(6);
        ReSetClear();
    }else if(Set == false && Clear == true){
        emit BT_Pressed(7);
        ReSetClear();
    }
}

void WinRight::on_BT_0_clicked()
{
    emit ChangePresetno(0);
    if(Set == false && Clear == false){
        emit BT_Pressed(5);
      //  qDebug()<<"call";
    }else if(Set == true && Clear == false){
        emit BT_Pressed(6); 
        ReSetClear();
     //   qDebug()<<"set";
    }else if(Set == false && Clear == true){
        emit BT_Pressed(7);
        ReSetClear();
     //   qDebug()<<"clear";
    }
}


void WinRight::ReSetClear()
{
    ui->BT_Set->setChecked(false);
    ui->BT_Clear->setChecked(false);
}



void WinRight::on_BT_Set_toggled(bool checked)
{
   // qDebug()<<"BT_Set";
    if(checked == true){
        Set = true;
    }else if(checked == false){
        Set = false;
    }
}

void WinRight::on_BT_Clear_toggled(bool checked)
{
   // qDebug()<<"BT_Clear";
    if(checked == true){
        Clear = true;
    }else if(checked == false){
        Clear = false;
    }
}

void WinRight::on_Box_Camera_USB_currentIndexChanged(int index)
{
    emit Setting_Press(index);
}



void WinRight::on_set_pan_tilt_clicked()
{
    emit BT_Pressed(8);
}

void WinRight::on_get_pan_tilt_clicked()
{
    emit BT_Pressed(9);
}

void WinRight::on_get_roll_clicked()
{
    emit BT_Pressed(10);
}
