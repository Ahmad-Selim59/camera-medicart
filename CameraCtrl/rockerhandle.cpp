#include "rockerhandle.h"

#include <QApplication>
#include <QDebug>
#include <QScreen>

RockerHandle::RockerHandle(QWidget *parent)
    : QWidget(parent)
{
    QList<QScreen*> screens = QApplication::screens();
    QScreen* screen = screens[0];
    qreal dpi = screen->logicalDotsPerInch();
    //计算dpi对应的缩放比例
    objectRate = dpi/96.0;   //缩放比例

    setWindowFlag(Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0x00,0xff,0x00,0x00));
    setPalette(pal);
    resize(100*objectRate,100*objectRate);
    mouseX=width()/2;
    mouseY=height()/2;
    tim=new QTimer(this);
    Speed = new QTimer(this);

    connect(tim,SIGNAL(timeout()),this,SLOT(getKeyNum()));      //获取方位
    connect(Speed,SIGNAL(timeout()),this,SLOT(SpeedChange()));  //发送速度
}

RockerHandle::~RockerHandle()
{

}
void RockerHandle::paintEvent(QPaintEvent *){
    QPainter painter(this);
    int side = qMin(width(), height()); //返回长宽中的最小值
    padR=side/2;                //底盘半径
    padX=padR;                  //底盘圆心
    padY=padR;                  //底盘圆心
    handleR=8*objectRate;      //摇杆圆半径 屏幕dpi为1时半径为8 根据屏幕dpi进行调整
    int handleMaxR=padR-handleR;    //外圆半径倒遥感圆的最大距离
    if(!mousePressed){//鼠标没按下则摇杆恢复到底盘中心
        mouseX=padX;
        mouseY=padY;
    }
    handPadDis=Pointdis(padR,padR,mouseX,mouseY);
    if(handPadDis<=handleMaxR){
        handleX=mouseX;
        handleY=mouseY;
    }
    else {
        handleX=(int)(handleMaxR*(mouseX-padX)/handPadDis+padX);
        handleY=(int)(handleMaxR*(mouseY-padY)/handPadDis+padY);
    }
    painter.setPen(Qt::NoPen);

    QLinearGradient Linear(handleX-handleR,handleX-handleR,handleX+handleR,handleX-handleR);    //设置渐变圆的原点和焦点在中心,半径8
    Linear.setColorAt(0,QColor(117,165,249));   //117,165,249
    Linear.setColorAt(1,QColor(86,133,215));    //86,133,215
    painter.setBrush(Linear);

    painter.drawEllipse(QPoint(handleX,handleY),handleR,handleR);//绘制一个圆摇杆

}

void RockerHandle::mouseMoveEvent(QMouseEvent* event){
    static bool r=false;
    mouseX=event->pos().x();
    mouseY=event->pos().y();
    if(r==true){
       update();
       r=false;
    }
    else{
        r=true;
    }
}

void RockerHandle::mouseReleaseEvent(QMouseEvent* event){
    mouseX=width()/2;
    mouseY=height()/2;
    tim->stop();
    Speed->stop();
    mousePressed=false;
    emit keyNumchanged(RockerHandle::stop);
    update();
}

void RockerHandle::mousePressEvent(QMouseEvent* event){
    mouseX=event->pos().x();
    mouseY=event->pos().y();
    tim->start(100);
    Speed->start(100);
    mousePressed=true;
    update();
}

//速度控制
void RockerHandle::SpeedChange()
{
    //50为dpi为1时的比例
    static int x,y;
    if(handleX<=50*objectRate){
        x = (50*objectRate-handleX)/(5*objectRate);
    }else{
        x = (handleX-50*objectRate)/(5*objectRate);
    }
    if(handleY<=50*objectRate){
        y = (50*objectRate-handleY)/(5*objectRate);
    }else{
        y = (handleY-50*objectRate)/(5*objectRate);
    }
//    qDebug()<<"x="<<x<<"  "<<"y="<<y;
    emit Speed_Pan(x);      //左右速度
    emit Speed_Tilt(y);     //上下速度
}

//可拖动的范围圆
double RockerHandle::Pointdis(int a,int b,int x,int y){
    return sqrt((double)((x-a)*(x-a)+(y-b)*(y-b)));
}

//方位控制
void RockerHandle::getKeyNum()
{
    temp45 = 50*objectRate-10*objectRate; //45
    temp55 = 50*objectRate+10*objectRate; //55

    if(handleX<=temp45 && handleY<=temp45){
        emit keyNumchanged(0);
        return;
    }else if(handleX<=temp45 && handleY>=temp55){
        emit keyNumchanged(6);
        return;
    }else if(handleX<=temp45 && handleY>=temp45 && handleY<=temp55){
        emit keyNumchanged(3);
        return;
    }

    if(handleX>=temp55 && handleY<=temp45){
        emit keyNumchanged(2);
        return;
    }else if(handleX>=temp55 && handleY>=temp55){
        emit keyNumchanged(8);
        return;
    }else if(handleX>=temp55 && handleY>=temp45 && handleY<=temp55){
        emit keyNumchanged(5);
        return;
    }

    if(handleX>=temp45 && handleX<=temp55 && handleY<=temp45){
        emit keyNumchanged(1);
        return;
    }
    if(handleX>=temp45 && handleX<=temp55 && handleY>=temp55){
        emit keyNumchanged(7);
        return;
    }
    emit keyNumchanged(4);
    return;
}
