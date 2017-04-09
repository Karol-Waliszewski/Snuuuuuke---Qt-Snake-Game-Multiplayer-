#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRectF>
#include <QLabel>

#include "snake.h"
#include "food.h"
#include "walls.h"

namespace Ui {
class MultiPlayer;
}

class MultiPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MultiPlayer(QWidget *parent = 0);
    ~MultiPlayer();
    void restart();
    void pause();
    void keyPressEvent(QKeyEvent *event);
    void GameOver(int p);
    void WindowStyleSheets();
    void paintEvent(QPaintEvent *pe);
public slots:
    void setSnakeSpeed(int s);
    void setSceneSize(QRectF rect);
    void setWalls(bool w);
    void setCollision(bool c);
    void setP1Name(QString n);
    void setP2Name(QString n);
    void setP1Brush(QColor c);
    void setP2Brush(QColor c);
signals:
    void currWindow(int i);
    void setDirection(int dir);
private slots:
    void on_menuButton_clicked();
    void on_pauseButton_clicked();
    void on_resetButton_clicked();
    void sUpdate();
    void placeWall();
private:
    Ui::MultiPlayer *ui;
    QTimer *timer;
    QGraphicsScene *scene;
    QRectF SceneSize;
    Snake *snake[3];
    Food *food;
    Walls *walls;
    QLabel *PointsLabel[3];

    int SnakeSpeed,Points[3];
    bool isWallsEnabled,isOtherColisionEnabled;
};

#endif // MULTIPLAYER_H
