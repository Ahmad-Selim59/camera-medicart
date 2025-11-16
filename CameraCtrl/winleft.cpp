#include "winleft.h"
#include "ui_winleft.h"
#include <QDebug>
#include <QScreen>

WinLeft::WinLeft(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinLeft)
{
    ui->setupUi(this);
}

WinLeft::~WinLeft()
{
    delete ui;
}

void WinLeft::on_Cb_WB_clicked(bool checked)
{
    if(checked)
    {
           emit BT_Pressed(1); //white balance auto;
    }else
    {
           emit BT_Pressed(2);//white balance manual;
    }

}


void WinLeft::on_BT_Flip_clicked()
{
   // qDebug()<<"flip";
    emit BT_Pressed(3);
}

void WinLeft::on_BT_Mirror_clicked()
{
   // qDebug()<<"mirror";
    emit BT_Pressed(4);
}
int menu_flag=1;
void WinLeft::on_BT_Menu_clicked()
{

    if(menu_flag)
    {
        ui->BT_Menu->setText("Menu ON");
        emit BT_Pressed(5);
        menu_flag=0;
    }
    else
    {
        ui->BT_Menu->setText("Menu OFF");
        emit BT_Pressed(10);
        menu_flag=1;
    }

}
void WinLeft::on_BT_HOME_clicked()
{
    emit BT_Pressed(6);
}

int ai_flag=0;
void WinLeft::on_BT_AI_clicked()
{
   // qDebug()<<"ai";

    if(ai_flag)
    {
        ui->BT_AI->setText("Framing");
        emit BT_Pressed(7);
        ai_flag=0;
    }
    else
    {
        ui->BT_AI->setText("Manual");
        emit BT_Pressed(8);
        ai_flag=1;
    }
}
void WinLeft::on_BT_PUSH_clicked()
{
    emit BT_Pressed(8);
}
void WinLeft::on_BT_Reset_clicked()
{
   // qDebug()<<"reset";
    emit BT_Pressed(9);
}

int IRON_flag=1;
void WinLeft::on_BT_IR_clicked()
{

    if(IRON_flag)
    {
        ui->BT_IR->setText("IR ON");
        emit BT_Pressed(11);
        IRON_flag=0;
    }
    else
    {
        ui->BT_IR->setText("IR OFF");
        emit BT_Pressed(12);
        IRON_flag=1;
    }

}

int DAY_flag=1;
void WinLeft::on_BT_DAY_clicked()
{

    if(DAY_flag)
    {
        ui->BT_DAY->setText("DAY");
        emit BT_Pressed(13);
        DAY_flag=0;
    }
    else
    {
        ui->BT_DAY->setText("NIGHT");
        emit BT_Pressed(14);
        DAY_flag=1;
    }

}


void WinLeft::on_BT_RST_PTZ_clicked()
{
    emit BT_Pressed(15);
}
