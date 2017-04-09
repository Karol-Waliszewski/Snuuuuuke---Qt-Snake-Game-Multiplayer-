#ifndef WALLS_H
#define WALLS_H

#include <QObject>
#include <QWidget>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class Walls : public QWidget
{
    Q_OBJECT
public:
    explicit Walls(QWidget *parent = 0);
    QGraphicsRectItem *wall;
    void createWalls(int w, int h);
signals:
    void setWall();
public slots:

private:
    QBrush WallBrush;
    QPen WallPen;
};

#endif // WALLS_H
