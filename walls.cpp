#include "walls.h"
#include <QColor>


Walls::Walls(QWidget *parent) : QWidget(parent)
{
    WallBrush.setColor(QColor(164, 175, 141));
    WallBrush.setStyle(Qt::SolidPattern);
    WallPen.setColor(QColor(164, 175, 141));
    WallPen.setWidthF(0.5);
}
void Walls::createWalls(int w,int h){
    wall = new QGraphicsRectItem;
    wall->setRect(0,0,w,20);
    wall->setBrush(WallBrush);
    wall->setPen(WallPen);
    wall->setZValue(-1);
    emit setWall();

    wall = new QGraphicsRectItem;
    wall->setRect(0,0,20,h);
    wall->setBrush(WallBrush);
    wall->setPen(WallPen);
    wall->setZValue(-1);
    emit setWall();

    wall = new QGraphicsRectItem;
    wall->setRect(w-20,0,20,h);
    wall->setBrush(WallBrush);
    wall->setPen(WallPen);
    wall->setZValue(-1);
    emit setWall();

    wall = new QGraphicsRectItem;
    wall->setRect(0,h-20,w,20);
    wall->setBrush(WallBrush);
    wall->setPen(WallPen);
    wall->setZValue(-1);
    emit setWall();
}
