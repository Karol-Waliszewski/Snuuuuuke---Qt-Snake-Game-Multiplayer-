#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRectF>

#include "snake.h"
#include "food.h"
#include "walls.h"

namespace Ui {
class SinglePlayer;
}

class SinglePlayer : public QWidget
{
    Q_OBJECT

public:
    explicit SinglePlayer(QWidget *parent = 0);
    ~SinglePlayer();
    void restart();
    void pause();
    void keyPressEvent(QKeyEvent *event);
    void GameOver();
    void WindowStyleSheets();
    void paintEvent(QPaintEvent *pe);
public slots:
    void setSnakeSpeed(int s);
    void setSceneSize(QRectF rect);
    void setWalls(bool w);
    void setP1Brush(QColor c);
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
    Ui::SinglePlayer *ui;
    QTimer *timer;
    QGraphicsScene *scene;
    QRectF SceneSize;
    Snake *snake;
    Food *food;
    Walls *walls;

    int SnakeSpeed,Points;
    bool isWallsEnabled;
};

#endif // SINGLEPLAYER_H
