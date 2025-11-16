#include "winsetting.h"
#include "ui_winsetting.h"

#include <QScreen>
#include <QDebug>
#include <QPainter>
WinSetting::WinSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinSetting)
{
    ui->setupUi(this);


    refreshDPI();
    setAttribute(Qt::WA_StyledBackground);        //使widget窗口使用样式表的颜色
    //this->setAutoFillBackground(true);          //使widget窗口不继承父窗口的背景色
        this->setAutoFillBackground(true);
    setWindowTitle("Setting");
    setWindowFlags(Qt::FramelessWindowHint);
}

WinSetting::~WinSetting()
{
    delete ui;
}

void WinSetting::refreshDPI()
{
    QList<QScreen*> screens = QApplication::screens();
    QScreen* screen = screens[0];
    qreal dpi = screen->logicalDotsPerInch();
    //计算dpi对应的缩放比例
    double objectRate = dpi/96.0;
    changeObjectSize(*this, objectRate);
    resize(width()*objectRate,height()*objectRate);
    connect(screen,SIGNAL(logicalDotsPerInchChanged(qreal)),this,SLOT(onLogicalDotsPerInchChanged(qreal)));
}

void WinSetting::onLogicalDotsPerInchChanged(qreal dpi)
{
    double objectRate = dpi/96.0;
    changeObjectSize(*this, objectRate);
    resize(width()*objectRate,height()*objectRate);
}

void WinSetting::changeObjectSize(const QObject &o, double objectRate)
{

    for (int i=0; i<o.children().size(); ++i) {
        QWidget *pWidget = qobject_cast<QWidget *>(o.children().at(i));
        if (pWidget != nullptr) {
            pWidget->setGeometry(pWidget->x()*objectRate,pWidget->y()*objectRate,
                                 pWidget->width()*objectRate, pWidget->height()*objectRate);
            changeObjectSize(*(o.children().at(i)),objectRate);
        }
    }
}

void WinSetting::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_pressed = true;
        m_pos = event->pos();
    }
}

void WinSetting::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pressed){
        move(event->pos() - m_pos + this->pos());
    }
}


void WinSetting::mouseReleaseEvent(QMouseEvent *event)
{
    m_pressed = false;
    QWidget::mouseReleaseEvent(event);
}

void WinSetting::on_BT_Close_clicked()
{
    this->hide();
}


void WinSetting::on_BT_Cancel_clicked()
{
    this->hide();
}

void WinSetting::on_BT_Apply_clicked()
{
    this->hide();
    emit Setting_Press(1);
}

void WinSetting::on_BT_Search_clicked()
{
    emit Setting_Press(2);
}

bool WinSetting::BoxFoucs()
{
    if(ui->Box_IP1->hasFocus() && ui->Box_IP2->hasFocus() || ui->Box_IP3->hasFocus() || ui->Box_IP4->hasFocus() || ui->Box_IP5->hasFocus() || ui->Box_IP6->hasFocus() ||ui->Box_IP7->hasFocus() ||
       ui->Box_Baudrate->hasFocus() || ui->Box_Com_Port->hasFocus() || ui->Box_Camera_USB->hasFocus() || ui->Box_Control_Port->hasFocus())
    {
        return false;
    }
    return true;
}

void WinSetting::on_Transparency_valueChanged(int value)
{
    double temp = value/10.0;
    setWindowOpacity(temp);
    emit TransparencyChange(value);

}


