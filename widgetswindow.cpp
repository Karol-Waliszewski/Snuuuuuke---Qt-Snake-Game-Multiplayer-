#include "widgetswindow.h"
#include "ui_widgetswindow.h"

WidgetsWindow::WidgetsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WidgetsWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->stackedWidget);
    setWindowTitle("Snuuuuuke");

    menu = new Menu;
    settings = new Settings;
    singleplayer = new SinglePlayer;
    multiplayer = new MultiPlayer;

    ui->stackedWidget->addWidget(menu);
    ui->stackedWidget->addWidget(settings);
    ui->stackedWidget->addWidget(singleplayer);
    ui->stackedWidget->addWidget(multiplayer);

    connect(menu,SIGNAL(currWindow(int)),this,SLOT(setWindow(int)));
    connect(settings,SIGNAL(currWindow(int)),this,SLOT(setWindow(int)));
    connect(singleplayer,SIGNAL(currWindow(int)),this,SLOT(setWindow(int)));
    connect(multiplayer,SIGNAL(currWindow(int)),this,SLOT(setWindow(int)));

    connect(settings,SIGNAL(wallsEnabled(bool)),singleplayer,SLOT(setWalls(bool)));
    connect(settings,SIGNAL(wallsEnabled(bool)),multiplayer,SLOT(setWalls(bool)));
    connect(settings,SIGNAL(eatingEnabled(bool)),multiplayer,SLOT(setCollision(bool)));
    connect(settings,SIGNAL(snakeSpeed(int)),singleplayer,SLOT(setSnakeSpeed(int)));
    connect(settings,SIGNAL(snakeSpeed(int)),multiplayer,SLOT(setSnakeSpeed(int)));
    connect(settings,SIGNAL(mapSize(QRectF)),singleplayer,SLOT(setSceneSize(QRectF)));
    connect(settings,SIGNAL(mapSize(QRectF)),multiplayer,SLOT(setSceneSize(QRectF)));
    connect(settings,SIGNAL(P1Name(QString)),multiplayer,SLOT(setP1Name(QString)));
    connect(settings,SIGNAL(P2Name(QString)),multiplayer,SLOT(setP2Name(QString)));
    connect(settings,SIGNAL(P1Brush(QColor)),singleplayer,SLOT(setP1Brush(QColor)));
    connect(settings,SIGNAL(P1Brush(QColor)),multiplayer,SLOT(setP1Brush(QColor)));
    connect(settings,SIGNAL(P2Brush(QColor)),multiplayer,SLOT(setP2Brush(QColor)));

    ui->stackedWidget->setCurrentIndex(0);
}

void WidgetsWindow::setWindow(int i) // 0 - MENU, 1 - SETTINGS, 2 - SINGLEPLAYER, 3 - MULTIPLAYER
{
    for(int j=0;j<4;j++){
        ui->stackedWidget->setCurrentIndex(j);
        ui->stackedWidget->currentWidget()->setFocusPolicy(Qt::NoFocus);
    }
    ui->stackedWidget->setCurrentIndex(i);
    ui->stackedWidget->currentWidget()->setFocusPolicy(Qt::StrongFocus);
    if(i==2)
        singleplayer->restart();
    if(i==3)
        multiplayer->restart();
}

WidgetsWindow::~WidgetsWindow()
{
    delete ui;
}
