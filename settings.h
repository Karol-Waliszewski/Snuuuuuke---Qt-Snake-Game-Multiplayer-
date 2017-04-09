#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    enum {ENABLED,DISABLED} walls,eating;
    enum {SLOW,NORMAL,FAST} speed;
    enum {SMALL,MEDIUM,LARGE} size;
    void CreateExamples(int i);
    void paintEvent(QPaintEvent *pe);
signals:
    void currWindow(int i);
    void snakeSpeed(int s);
    void mapSize(QRectF r);
    void wallsEnabled(bool w);
    void eatingEnabled(bool e);
    void P1Name(QString name);
    void P2Name(QString name);
    void P1Brush(QColor color);
    void P2Brush(QColor color);
private slots:
    void on_menuButton_clicked();
    void on_MSRB_clicked();
    void on_MSLB_clicked();
    void on_SSRB_clicked();
    void on_SSLB_clicked();
    void on_WRB_clicked();
    void on_WLB_clicked();
    void on_P1LE_textChanged(const QString &arg1);
    void on_P2LE_textChanged(const QString &arg1);
    void on_P1SCB_clicked();
    void on_P2SCB_clicked();
    void on_E2PL_clicked();
    void on_E2PR_clicked();

private:
    Ui::Settings *ui;
    QColor PC[3];
    QGraphicsScene *SceneP[3];
    QGraphicsRectItem  *ExampleHead,*ExampleBody;
    QGraphicsEllipseItem *Food;
};

#endif // SETTINGS_H
