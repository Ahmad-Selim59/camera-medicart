#ifndef WINLEFT_H
#define WINLEFT_H

#include <QWidget>

namespace Ui {
class WinLeft;
}

class WinLeft : public QWidget
{
    Q_OBJECT

public:
    explicit WinLeft(QWidget *parent = nullptr);
    ~WinLeft();

signals:
    void BT_Pressed(int flat);
private slots:

    void on_BT_Flip_clicked();
    void on_BT_Mirror_clicked();
    void on_BT_Menu_clicked();
    void on_BT_HOME_clicked();
    void on_BT_AI_clicked();
    void on_BT_PUSH_clicked();
    void on_BT_Reset_clicked();
    void on_Cb_WB_clicked(bool checked);

    void on_BT_IR_clicked();

    void on_BT_DAY_clicked();



    void on_BT_RST_PTZ_clicked();

private:
    Ui::WinLeft *ui;
};

#endif // WINLEFT_H
