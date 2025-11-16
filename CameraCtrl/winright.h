#ifndef WINRIGHT_H
#define WINRIGHT_H

#include <QWidget>

namespace Ui {
class WinRight;
}

class WinRight : public QWidget
{
    Q_OBJECT

public:
    explicit WinRight(QWidget *parent = nullptr);
    ~WinRight();
    void ReSetClear();

signals:
    void keyNumchanged(int num);
    void Speed_Pan(int num);
    void Speed_Tilt(int num);
    void IPCAMChange(int num);
    void AF_MF_Push(int num);
    void ChangePresetno(int num);

    void BT_Pressed(int flag);
    void BT_Show(bool flag);
    void Setting_Press(int flag);
private slots:

    void TP_key(int num);
    void TP_Pan(int num);
    void TP_Tilt(int num);






void on_BT_Top_toggled(bool checked);
void on_BT_Close_clicked();
void on_toolButton_clicked();//显示 隐藏左侧



void on_Slider_Zoom_valueChanged(int value);

void on_Slider_Zoom_sliderReleased();


void on_BT_1_clicked();
void on_BT_2_clicked();
void on_BT_3_clicked();
void on_BT_4_clicked();
void on_BT_5_clicked();
void on_BT_6_clicked();
void on_BT_7_clicked();
void on_BT_8_clicked();
void on_BT_0_clicked();


void on_BT_Set_toggled(bool checked);

void on_BT_Clear_toggled(bool checked);

void on_Box_Camera_USB_currentIndexChanged(int index);


void on_set_pan_tilt_clicked();

void on_get_pan_tilt_clicked();

void on_get_roll_clicked();

private:
    Ui::WinRight *ui;
    bool WinShow;

    bool Set,Clear;
};

#endif // WINRIGHT_H
