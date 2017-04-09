#include "snake.h"
#include <QMessageBox>
#include "cstdlib"

Snake::Snake(QWidget *parent) : QWidget(parent){
    SnakeHeadBrush.setColor(Qt::darkGray);
    SnakeHeadBrush.setStyle(Qt::SolidPattern);

    SnakeTailBrush.setColor(Qt::lightGray);
    SnakeTailBrush.setStyle(Qt::SolidPattern);

    SnakePen.setColor(QColor(164, 175, 141));
    SnakePen.setWidthF(0.6);
    x=0;y=20;horizontal = 20; vertical = 0;
}

void Snake::CreateHead(int w, int h){
    SnakeHead = new QGraphicsRectItem;
    x = (qrand()%(w-60+1))+20;
    x = x - (x%20);
    y = (qrand()%(h-60+1))+20;
    y = y - (y%20);
    horizontal = 20; vertical = 0;
    if(x>w/2)
        horizontal = -20;
    SnakeHead->setRect(0,0,20,20);
    SnakeHead->setPos(x,y);
    SnakeHead->setBrush(SnakeHeadBrush);
    SnakeHead->setPen(SnakePen);
    SnakeHead->setZValue(10);
    SnakeTail.clear();
}

void Snake::CreateBody(){
    SnakeBody = new QGraphicsRectItem;
    SnakeBody->setRect(0,0,20,20);
    SnakeBody->setPos(-20,-20);
    SnakeBody->setBrush(SnakeTailBrush);
    SnakeBody->setPen(SnakePen);
    SnakeTail.append(SnakeBody);
}

void Snake::SnakeUpdate(int height, int width){

    prevPos = SnakeHead->pos();
    x=(x+horizontal)%width;
    y=(y+vertical)%height;
    if(x<0) x=width-20;
    if(y<0) y=height-20;
    SnakeHead->setPos(x,y);

    if(SnakeTail.isEmpty()==false){
    if(SnakeTail.size()>1)
     for(int i=SnakeTail.size()-1;i>=1;i--)
        SnakeTail.at(i)->setPos(SnakeTail.at(i-1)->pos());
    SnakeTail.first()->setPos(prevPos);
    }
}

bool Snake::selfColision(){
    for(int i=SnakeTail.size()-1;i>=0;i--){
        if(SnakeTail.at(i)->pos()==SnakeHead->pos())
            return true;
    }
    return false;
}

bool Snake::otherColision(QPointF pos){
    for(int i=SnakeTail.size()-1;i>=0;i--){
        if(SnakeTail.at(i)->pos()==pos)
            return true;
    }
    return false;
}

void Snake::setHeadBrush(QColor color){
    SnakeHeadBrush.setColor(color);
}

void Snake::setTailBrush(QColor color){
    SnakeTailBrush.setColor(color);
}

void Snake::changeDirection(int dir){

    if(dir == 0){
        if(SnakeTail.size() >= 2 && vertical != 0)
            return;
        horizontal = 0; vertical = -20;
    }
    if(dir == 1){
        if(SnakeTail.size() >= 2 && vertical != 0)
            return;
        horizontal = 0; vertical = 20;
    }
    if(dir == 2){
        if(SnakeTail.size() >= 2 && horizontal != 0)
            return;
        horizontal = -20; vertical = 0;
    }
    if(dir == 3){
        if(SnakeTail.size() >= 2 && horizontal != 0)
            return;
        horizontal = 20; vertical = 0;
    }
}
