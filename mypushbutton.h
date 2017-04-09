#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = 0);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
signals:
    void HowToPlay();
    void Logo();
    void Credits();
public slots:
};

#endif // MYPUSHBUTTON_H
