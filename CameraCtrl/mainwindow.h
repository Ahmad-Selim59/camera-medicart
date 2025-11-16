#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "CameraCtrl.h"
#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QMouseEvent>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QTimer>
#include <QTimerEvent>
#include <QScreen>
#include "myqcombobox.h"
#include <windows.h>
#include <dbt.h>
#include <devguid.h>
#include <setupapi.h>
#include <initguid.h>
#include <QDebug>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void ModeChange(int);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*程序启动初始化*/
	//更具屏幕缩放DIP调整程序界面大小，只能启动时调整，动态随DPI调整会有很多意想不到的bug
    void refreshDPI();
    //参数初始化
    void InitValue();
	//初始化整体窗口
    void InitWindows();
	//寻找widget中子类控件的指针
    void InitFindChild();
	//链接控件指针的各种信号到相关槽函数
    void InitConnect();
	//注册USB、串口热插拔
    void InitUSBGuid();
	//判断窗口是不是贴边状态
    bool Screen_edge();
	//弹出警告窗口
    void Warn_NoDev();
    /*打开摄像头初始化*/
    //void Value_Init(BaseDevice *dev);
	//在摄像头打开的途中点击Reset按钮
    void Value_Reset(BaseDevice *dev);
	//遥感移动
    void MoveEvent(BaseDevice *dev,int place,int x,int y);
private slots:
	//窗口DPI缩放相关
    void changeObjectSize(const QObject &o, double objectRate);
    void onLogicalDotsPerInchChanged(qreal dpi);
	//鼠标点击拖动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
	//USB、串口热插拔相关
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	//窗口靠边隐藏、隐藏状态下显示相关
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
	//无用
    void timerEvent(QTimerEvent *event);
	//启动窗口后
    void TimerInit();
    void DeviceChange();
	/*左侧窗口*/
    void LWin_BT_Pressed(int flag);
    void Tool_Show(bool flag);
    void FlickerChange();

    void Brightness_Change(int position);
    void Contrast_Change(int position);
    void Hue_Change(int position);
    void Saturation_Change(int position);
    void Sharpness_Change(int position);
    void Gamma_Change(int position);
    void BLC_Change(int position);
    void WB_Change(int position);
    /*右侧窗口*/
	void RWin_BT_Pressed(int flag);
    void IPCAMChange(int flag);
    void MovePlace(int num);
    void SpeedX(int num);
    void SpeedY(int num);
    void FocusChange();
    void ZoomChange();
    void FucusStop();
    void ZoomStop();
    void AF_MF_Push(int num);
    void ChangePresetno(int num);

    void Setting_Press(int flag);

    bool sleep(unsigned int msec);

private:
    Ui::MainWindow *ui;
    bool InitRun;
    QPoint m_pos;
    bool m_pressed;
    bool hide_flag;
    bool R_Hide;
    bool Show_flag;                 //true展开 false收缩
    bool Focus;
    bool TopFlag;       //置顶状态

    int TimerID_ComboBox;
    QTimer *Tim;
    QTimer *ChangeTimer;
    DeviceList USB_List;
    BaseDevice *USB_Dev;
    bool USB_Mode;

	bool WDR_flag;

    /*左侧窗口*/

    QComboBox *ComboBox_Flicker;

    QSlider *slider_brightness;
    QSlider *slider_contrast;
    QSlider *slider_hue;
    QSlider *slider_saturation;
    QSlider *slider_sharpness;
    QSlider *slider_gamma;
    QSlider *slider_blc;
    QSlider *slider_wb;


    QLineEdit *v_brightness;
    QLineEdit *v_contrast;
    QLineEdit *v_hue;
    QLineEdit *v_saturation;
    QLineEdit *v_sharpness;
    QLineEdit *v_gamma;
    QLineEdit *v_blc;
    QLineEdit *v_wb;

    QCheckBox *cb_wb;


    QLineEdit *v_set_pan_data;
    QLineEdit *v_set_tilt_data;
    QLineEdit *v_get_pan_data;
    QLineEdit *v_get_tilt_data;
    QLineEdit *v_get_roll_data;





    /*右侧窗口*/
    int IPCAM;
	QSlider *Slider_Fucus;
    QSlider *Slider_Zoom;
    int foucs_num_L,foucs_num_R;
    int zoom_num_L,zoom_num_R;
    int Presetno;
    int MoveChange;
    int XChange;
    int YChange;
    QPushButton *BT_AF;
    QComboBox *Box_Camera_USB;



    int lwidth,fwidth;
    int lheight,fheight;
    bool InitApp;

    long flip=0,mirror=0,menu=0,ai=0;
//long uflip,umirror;

};
#endif // MAINWINDOW_H


























