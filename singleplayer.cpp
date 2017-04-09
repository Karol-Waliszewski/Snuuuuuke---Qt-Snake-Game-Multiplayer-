#include "singleplayer.h"
#include "ui_singleplayer.h"
#include <QMessageBox>

SinglePlayer::SinglePlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SinglePlayer){
    ui->setupUi(this);
    SceneSize.setRect(0,0,600,400);

    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->graphicsView->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    ui->menuButton->setFocusPolicy(Qt::NoFocus);
    ui->pauseButton->setFocusPolicy(Qt::NoFocus);
    ui->resetButton->setFocusPolicy(Qt::NoFocus);

    timer = new QTimer;
    SnakeSpeed = 150;
    connect(timer,SIGNAL(timeout()),this,SLOT(sUpdate()));
    isWallsEnabled=true;
    snake = new Snake;

    setP1Brush(QColor(0,85,255));
}

//--------------------GAMESTART/RESTART--------------------//

void SinglePlayer::restart(){
    scene = new QGraphicsScene();

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

    snake->CreateHead(SceneSize.width(),SceneSize.height());

    food = new Food;
    food->createFruit(SceneSize.width(),SceneSize.height());

    scene->addItem(snake->SnakeHead);
    scene->addItem(food->fruit);

    Points = 0;
    ui->PointsLabel->setText("0");
    WindowStyleSheets();

    ui->pauseButton->setText("Pause");
    ui->pauseButton->show();   
}

void SinglePlayer::placeWall(){
    scene->addItem(walls->wall);
}


//------------------------CONTROLS------------------------//

void SinglePlayer::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Up)
        snake->changeDirection(0);
    if(event->key()==Qt::Key_Down)
        snake->changeDirection(1);
    if(event->key()==Qt::Key_Left)
        snake->changeDirection(2);
    if(event->key()==Qt::Key_Right)
        snake->changeDirection(3);

    if(event->key()==Qt::Key_Space)
        restart();

    if(event->key()==Qt::Key_Control)
        pause();
}

//------------------------GAMECORE------------------------//

void SinglePlayer::sUpdate(){
    snake->SnakeUpdate(SceneSize.height(),SceneSize.width());
    if(snake->SnakeHead->pos()==food->fruit->pos()){
        scene->removeItem(food->fruit);
        food->createFruit(SceneSize.width(),SceneSize.height());
        snake->CreateBody();
        scene->addItem(snake->SnakeBody);
        scene->addItem(food->fruit);
        Points++;
        ui->PointsLabel->setText(QString::number(Points));
    }
    if(isWallsEnabled)
        if(snake->SnakeHead->x()<20 || snake->SnakeHead->x()>=SceneSize.width()-20|| snake->SnakeHead->y()<20 || snake->SnakeHead->y()>=SceneSize.height()-20)
            GameOver();
    if(snake->selfColision())
        GameOver();
}

void SinglePlayer::GameOver(){
    timer->stop();
    ui->pauseButton->hide();
    QMessageBox::warning(this,"GAME OVER","YOU LOST!!");
}

void SinglePlayer::pause(){
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

void SinglePlayer::setSnakeSpeed(int s){
    SnakeSpeed = s;
}

void SinglePlayer::setSceneSize(QRectF rect){
    SceneSize = rect;
}

void SinglePlayer::setWalls(bool w){
    isWallsEnabled = w;
}

void SinglePlayer::setP1Brush(QColor c){
    snake->setHeadBrush(c);
    c.setHsv(c.hsvHue()+20,c.hsvSaturation()-10,c.value());
    snake->setTailBrush(c);
}

//------------------------BUTTONS------------------------//

void SinglePlayer::on_menuButton_clicked(){
    emit currWindow(0);
    ui->pauseButton->setText("Pause");
    timer->stop();
}

void SinglePlayer::on_pauseButton_clicked(){
    pause();
}

void SinglePlayer::on_resetButton_clicked(){
    restart();
}

//----------------------STYLESHEETS----------------------//

void SinglePlayer::WindowStyleSheets(){
    this->setObjectName("Background");
    this->setStyleSheet("#Background{background-image: url(:/menu/img/ALLGAMEBG.png);};");
    QBrush brushi;
    brushi.setStyle(Qt::SolidPattern);
    brushi.setColor(QColor(23, 53, 41));
    scene->setBackgroundBrush(brushi);
}
void SinglePlayer::paintEvent(QPaintEvent *pe){
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
//-------------------------------------------------------//

SinglePlayer::~SinglePlayer(){
    delete ui;
}
