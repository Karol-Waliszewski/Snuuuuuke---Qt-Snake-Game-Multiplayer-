#ifndef WIDGETSWINDOW_H
#define WIDGETSWINDOW_H

#include <QMainWindow>

#include "menu.h"
#include "settings.h"
#include "singleplayer.h"
#include "multiplayer.h"

namespace Ui {
class WidgetsWindow;
}

class WidgetsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WidgetsWindow(QWidget *parent = 0);
    ~WidgetsWindow();
public slots:
    void setWindow(int i);
private:
    Ui::WidgetsWindow *ui;
    Menu *menu;
    Settings *settings;
    SinglePlayer *singleplayer;
    MultiPlayer *multiplayer;
};

#endif // WIDGETSWINDOW_H
