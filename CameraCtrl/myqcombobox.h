#ifndef MYQCOMBOBOX_H
#define MYQCOMBOBOX_H

#include <QComboBox>
#include <QEvent>
#include <QDebug>

class myQComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit myQComboBox(QWidget *parent = 0);
    ~myQComboBox();
    bool GetOpen();
private slots:
    void showPopup();
    void hidePopup();
private:
    bool open;
};

#endif // MYQCOMBOBOX_H
