#include "widgetswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetsWindow w;
    w.show();

    return a.exec();
}
