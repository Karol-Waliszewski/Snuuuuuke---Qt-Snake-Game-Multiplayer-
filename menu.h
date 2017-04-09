#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();
    void paintEvent(QPaintEvent *pe);
signals:
    void currWindow(int i);
private slots:
    void on_quitButton_clicked();
    void on_spButton_clicked();
    void on_mpButton_clicked();
    void on_settingsButton_clicked();
    void on_HTPButton_clicked();
    void on_creditsButton_clicked();
    void setHowToPlay();
    void setLogo();
    void setCredits();
private:
    Ui::Menu *ui;
    QPixmap *Credits,*HowToPlay,*Logo;
};

#endif // MENU_H
