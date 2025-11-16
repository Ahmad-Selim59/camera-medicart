#ifndef WINSETTING_H
#define WINSETTING_H

#include <QMouseEvent>
#include <QWidget>

namespace Ui {
class WinSetting;
}

class WinSetting : public QWidget
{
    Q_OBJECT
signals:
    void TransparencyChange(int num);
public:
    explicit WinSetting(QWidget *parent = nullptr);
    ~WinSetting();
    void refreshDPI();
    bool BoxFoucs();
private slots:
    void changeObjectSize(const QObject &o, double objectRate);
    void onLogicalDotsPerInchChanged(qreal dpi);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void on_BT_Close_clicked();

    void on_BT_Cancel_clicked();

    void on_BT_Apply_clicked();

    void on_BT_Search_clicked();

    void on_Transparency_valueChanged(int value);

//    void paintEvent(QPaintEvent *e);

signals:
    void Setting_Press(int flag);
private:
    Ui::WinSetting *ui;
    QPoint m_pos;
    bool m_pressed;
};

#endif // WINSETTING_H
