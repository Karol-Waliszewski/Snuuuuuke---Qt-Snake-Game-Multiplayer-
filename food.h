#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QWidget>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

class Food : public QWidget
{
    Q_OBJECT
public:
    explicit Food(QWidget *parent = 0);
    QGraphicsEllipseItem *fruit;
    void createFruit(int w,int h);
signals:

public slots:
private:
    int x,y;
    QBrush FoodBrush;
    QPen FoodPen;
};

#endif // FOOD_H
