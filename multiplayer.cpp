#include "multiplayer.h"
#include "ui_multiplayer.h"
#include <QMessageBox>
#include <QFont>
#include <QPixmap>

MultiPlayer::MultiPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiPlayer)
{
    ui->setupUi(this);
    SceneSize.setRect(0,0,600,400);

    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    ui->menuButton->setFocusPolicy(Qt::NoFocus);
    ui->pauseButton->setFocusPolicy(Qt::NoFocus);
    ui->resetButton->setFocusPolicy(Qt::NoFocus);

    QFont font("Agency FB",28);
    font.setBold(true);
    for(int i=1;i<3;i++){
    PointsLabel[i] = new QLabel;
    PointsLabel[i]->setFont(font);
    PointsLabel[i]->setAlignment(Qt::AlignCenter);
    }
    ui->verticalLayout->addWidget(PointsLabel[1]);
    ui->verticalLayout_2->addWidget(PointsLabel[2]);
    timer = new QTimer;
    SnakeSpeed = 150;
    snake[1] = new Snake;
    snake[2] = new Snake;
    connect(timer,SIGNAL(timeout()),this,SLOT(sUpdate()));
    isWallsEnabled=true;
    isOtherColisionEnabled=true;
    setP1Brush(QColor(0,85,255));
    setP2Brush(QColor(0,255,127));
}

//--------------------GAMESTART/RESTART--------------------//

void MultiPlayer::restart(){
    scene = new QGraphicsScene;
    scene->setSceneRect(SceneSize);

    ui->graphicsView->setMinimumSize(SceneSize.width(),SceneSize.height());
    ui->graphicsView->setMaximumSize(SceneSize.width(),SceneSize.height());
    ui->graphicsView->translate(0,0);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setSceneRect(SceneSize);

    timer->stop();
    timer->start(SnakeSpeed);

    if(isWallsEnabled){
        walls = new Walls;
        connect(walls,SIGNAL(setWall()),this,SLOT(placeWall()));
        walls->createWalls(SceneSize.width(),SceneSize.height());
    }
    for(int i=1;i<3;i++){
    snake[i]->CreateHead(SceneSize.width(),SceneSize.height());
    scene->addItem(snake[i]->SnakeHead);
    Points[i] = 0;
    PointsLabel[i]->setText("0");
    }

    food = new Food;
    food->createFruit(SceneSize.width(),SceneSize.height());
    scene->addItem(food->fruit);

    WindowStyleSheets();

    ui->pauseButton->setText("Pause");
    ui->pauseButton->show();
}

void MultiPlayer::placeWall(){
    scene->addItem(walls->wall);
}

//------------------------CONTROLS------------------------//

void MultiPlayer::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Up)
        snake[1]->changeDirection(0);
    if(event->key()==Qt::Key_Down)
        snake[1]->changeDirection(1);
    if(event->key()==Qt::Key_Left)
        snake[1]->changeDirection(2);
    if(event->key()==Qt::Key_Right)
        snake[1]->changeDirection(3);

    if(event->key()==Qt::Key_W)
        snake[2]->changeDirection(0);
    if(event->key()==Qt::Key_S)
        snake[2]->changeDirection(1);
    if(event->key()==Qt::Key_A)
        snake[2]->changeDirection(2);
    if(event->key()==Qt::Key_D)
        snake[2]->changeDirection(3);

    if(event->key()==Qt::Key_Space)
        restart();

    if(event->key()==Qt::Key_Control)
        pause();
}

//------------------------GAMECORE------------------------//

void MultiPlayer::sUpdate(){
    for(int i=1;i<3;i++){
    snake[i]->SnakeUpdate(SceneSize.height(),SceneSize.width());
    if(snake[i]->SnakeHead->pos()==food->fruit->pos()){
        scene->removeItem(food->fruit);
        food->createFruit(SceneSize.width(),SceneSize.height());
        snake[i]->CreateBody();
        scene->addItem(snake[i]->SnakeBody);
        scene->addItem(food->fruit);
        Points[i]++;
        PointsLabel[i]->setText(QString::number(Points[i]));
    }
    if(isWallsEnabled)
        if(snake[i]->SnakeHead->x()<20 || snake[i]->SnakeHead->x()>=SceneSize.width()-20|| snake[i]->SnakeHead->y()<20 || snake[i]->SnakeHead->y()>=SceneSize.height()-20)
            GameOver(i);
    if(snake[i]->selfColision())
        GameOver(i);
    }
    if(isOtherColisionEnabled){
        if(snake[1]->otherColision(snake[2]->SnakeHead->pos()))
            GameOver(2);
        if(snake[2]->otherColision(snake[1]->SnakeHead->pos()))
            GameOver(1);
    }
}

void MultiPlayer::GameOver(int p){
    timer->stop();
    ui->pauseButton->hide();
    if(p == 1)
        QMessageBox::warning(this,"GAME OVER",ui->label->text() + " LOST!!");
    else
        QMessageBox::warning(this,"GAME OVER",ui->label_2->text() + " LOST!!");
}

void MultiPlayer::pause(){
    if(ui->pauseButton->text() == "Pause"){
        timer->stop();
        ui->pauseButton->setText("Start");
    }
    else{
        timer->start(SnakeSpeed);
        ui->pauseButton->setText("Pause");
    }
}

//--------------------SETTINGS OPTIONS--------------------//

void MultiPlayer::setSnakeSpeed(int s){
    SnakeSpeed = s;
}

void MultiPlayer::setSceneSize(QRectF rect){
    SceneSize = rect;
}

void MultiPlayer::setWalls(bool w){
    isWallsEnabled = w;
}

void MultiPlayer::setCollision(bool c){
    isOtherColisionEnabled = c;
}

void MultiPlayer::setP1Name(QString n){
    ui->label->setText(n);
}

void MultiPlayer::setP2Name(QString n){
    ui->label_2->setText(n);
}

void MultiPlayer::setP1Brush(QColor c){
    snake[1]->setHeadBrush(c);
    c.setHsv(c.hsvHue()+20,c.hsvSaturation()-10,c.value());
    snake[1]->setTailBrush(c);
}

void MultiPlayer::setP2Brush(QColor c){
    snake[2]->setHeadBrush(c);
    c.setHsv(c.hsvHue()+20,c.hsvSaturation()-10,c.value());
    snake[2]->setTailBrush(c);
}

//------------------------BUTTONS------------------------//

void MultiPlayer::on_menuButton_clicked(){
    emit currWindow(0);
    ui->graphicsView->setMinimumSize(0,0);
    ui->pauseButton->setText("Pause");
    timer->stop();
}

void MultiPlayer::on_pauseButton_clicked(){
    pause();
}

void MultiPlayer::on_resetButton_clicked(){
    restart();
}

//----------------------STYLESHEETS-----------------------//

void MultiPlayer::WindowStyleSheets(){
    this->setObjectName("Background");
    this->setStyleSheet("#Background{background-image: url(:/menu/img/ALLGAMEBG.png);};");
    QBrush brushi;
    brushi.setStyle(Qt::SolidPattern);
    brushi.setColor(QColor(23, 53, 41));
    scene->setBackgroundBrush(brushi);
    PointsLabel[1]->setStyleSheet("color: rgb(164, 175, 141);");
    PointsLabel[2]->setStyleSheet("color: rgb(164, 175, 141);");
}

//-------------------------------------------------------//

void MultiPlayer::paintEvent(QPaintEvent *pe){
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

MultiPlayer::~MultiPlayer()
{
    delete ui;
}
