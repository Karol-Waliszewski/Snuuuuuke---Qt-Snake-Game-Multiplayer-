#include "mypushbutton.h"
#include <QMessageBox>


MyPushButton::MyPushButton(QWidget *parent)
{
    setMouseTracking(true);
}

void MyPushButton::enterEvent(QEvent *event){
    setStyleSheet("border-image: url(:/menu/img/ButtonFrameActive.png); background-image: url(:/menu/img/ALLGAMEBG.png); background-position: center;background-repeat: no-repeat; background-attachment: fixed; color: rgb(120, 126, 105);");
    if(this->text()=="How To Play?")
     emit HowToPlay();
    if(this->text()=="Credits")
     emit Credits();
    QPushButton::enterEvent(event);
}

void MyPushButton::leaveEvent(QEvent *event){
    setStyleSheet("border-image: url(:/menu/img/ButtonFrame.png); background-image: url(:/menu/img/ALLGAMEBG.png); background-position: center;background-repeat: no-repeat; background-attachment: fixed; color: rgb(164, 175, 141);");
    emit Logo();
    QPushButton::leaveEvent(event);
}
