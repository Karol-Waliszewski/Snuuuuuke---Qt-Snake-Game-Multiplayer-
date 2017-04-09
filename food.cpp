#include "food.h"
#include "cstdlib"

Food::Food(QWidget *parent) : QWidget(parent)
{
    FoodBrush.setColor(Qt::red);
    FoodBrush.setStyle(Qt::Dense3Pattern);

    FoodPen.setColor(QColor(164, 175, 141));
    FoodPen.setWidthF(0.2);
}

void Food::createFruit(int w, int h)
{
    fruit = new QGraphicsEllipseItem;
    fruit->setZValue(-2);
    x = (qrand()%(w-60+1))+20;
    x = x - (x%20);
    y = (qrand()%(h-60+1))+20;
    y = y - (y%20);
    fruit->setRect(0,0,20,20);
    fruit->setPos(x,y);
    fruit->setBrush(FoodBrush);
    fruit->setPen(FoodPen);
}
