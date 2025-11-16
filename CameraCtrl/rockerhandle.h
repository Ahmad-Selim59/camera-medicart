#ifndef ROCKERHANDLE_H
#define ROCKERHANDLE_H

#include <QWidget>
#include <QPainter>
#include <QDrag>
#include <QMouseEvent>
#include <QtMath>
#include <QTimer>
#include <QDebug>
class RockerHandle : public QWidget
{
    Q_OBJECT
public:
    //    explicit RockerHandle(QWidget *parent = nullptr);
    RockerHandle(QWidget *parent = 0);
    ~RockerHandle();
    enum {upleft=0,up,upright,left,stop,right,downleft,down,downright};
signals:
    void keyNumchanged(int num);
    void Speed_Pan(int num);
    void Speed_Tilt(int num);
protected:
    void paintEvent(QPaintEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    //  void resizeEvent(QResizeEvent *event)override;


private slots:
    void SpeedChange();
    void getKeyNum();

private:
    int mouseX;
    int mouseY;
    int handleX;//摇杆
    int handleY;
    int handleR;
    int padX;//底盘
    int padY;
    int padR;
    double handPadDis;//两圆圆心距离
    bool mousePressed;
    QTimer *tim;
    QTimer *Speed;

    //dpi缩放部分
    double objectRate;  //缩放比例
    int temp45,temp55;    //方向
private:
    double Pointdis(int a,int b,int x,int y);//两点距离
};

#endif // ROCKERHANDLE_H
