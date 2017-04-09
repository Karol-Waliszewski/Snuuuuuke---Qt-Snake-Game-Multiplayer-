#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QList>
#include <QBrush>
#include <QPen>
#include <QPointF>

class Snake : public QWidget
{
    Q_OBJECT

public:
    explicit Snake(QWidget *parent = 0);
    void CreateHead(int w, int h);
    void CreateBody();
    void setHeadBrush(QColor color);
    void setTailBrush(QColor color);
    void changeDirection(int dir);
    bool selfColision();
    bool otherColision(QPointF pos);
    QGraphicsRectItem *SnakeHead;
    QGraphicsRectItem *SnakeBody;
signals:

public slots:
    void SnakeUpdate(int height, int width);
private:
    int x,y,horizontal,vertical;
    QBrush SnakeHeadBrush;
    QBrush SnakeTailBrush;
    QPen SnakePen;
    QList<QGraphicsRectItem*> SnakeTail;
    QPointF prevPos;
};

#endif // SNAKE_H
