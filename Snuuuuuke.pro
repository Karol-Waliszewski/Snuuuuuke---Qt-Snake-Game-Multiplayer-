#-------------------------------------------------
#
# Project created by QtCreator 2017-01-04T22:08:25
#
#-------------------------------------------------

QT       += core gui
win32:RC_ICONS += :/img/wonsz.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snuuuuuke
TEMPLATE = app


SOURCES += main.cpp\
        widgetswindow.cpp \
    menu.cpp \
    settings.cpp \
    singleplayer.cpp \
    multiplayer.cpp \
    snake.cpp \
    food.cpp \
    walls.cpp \
    mypushbutton.cpp

HEADERS  += widgetswindow.h \
    menu.h \
    settings.h \
    singleplayer.h \
    multiplayer.h \
    snake.h \
    food.h \
    walls.h \
    mypushbutton.h

FORMS    += widgetswindow.ui \
    menu.ui \
    settings.ui \
    singleplayer.ui \
    multiplayer.ui

RESOURCES += \
    resources.qrc
