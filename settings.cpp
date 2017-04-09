#include "settings.h"
#include "ui_settings.h"
#include <QColorDialog>

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    size = MEDIUM;
    speed = NORMAL;
    walls = ENABLED;
    eating = ENABLED;
    SceneP[1] = new QGraphicsScene;
    SceneP[2] = new QGraphicsScene;
    ui->graphicsView->setScene(SceneP[1]);
    ui->graphicsView->setSceneRect(0,0,200,200);
    ui->graphicsView_2->setScene(SceneP[2]);
    ui->graphicsView_2->setSceneRect(0,0,200,200);
    PC[1] = QColor(0,85,255);
    PC[2] = QColor(0,255,127);
    CreateExamples(1);
    CreateExamples(2);

//----------------------GRAPHICS----------------------//

    this->setObjectName("Background");
    this->setStyleSheet("#Background{background-image: url(:/menu/img/ALLGAMEBG.png);};");
    QBrush brushi;
    brushi.setStyle(Qt::SolidPattern);
    brushi.setColor(QColor(23, 53, 41));
    SceneP[1]->setBackgroundBrush(brushi);
    SceneP[2]->setBackgroundBrush(brushi);
}

void Settings::paintEvent(QPaintEvent *pe){
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_menuButton_clicked()
{
    emit currWindow(0);
}

void Settings::on_MSRB_clicked()
{
    QRect rectangle;

    switch(size)
    {
    case SMALL:
        size = MEDIUM;
        ui->MSL->setText("Medium");
        rectangle.setRect(0,0,600,400);
        emit mapSize(rectangle);
        break;
    case MEDIUM:
        size = LARGE;
        ui->MSL->setText("Large");
        rectangle.setRect(0,0,800,600);
        emit mapSize(rectangle);
        break;
    case LARGE:
        break;
    }
}

void Settings::on_MSLB_clicked()
{
    QRect rectangle;

    switch(size)
    {
    case SMALL:
        break;
    case MEDIUM:
        size = SMALL;
        ui->MSL->setText("Small");
        rectangle.setRect(0,0,400,200);
        emit mapSize(rectangle);
        break;
    case LARGE:
        size = MEDIUM;
        ui->MSL->setText("Medium");
        rectangle.setRect(0,0,600,400);
        emit mapSize(rectangle);
        break;
    }
}

void Settings::on_SSRB_clicked()
{
    switch(speed)
    {
    case SLOW:
        speed = NORMAL;
        ui->SSL->setText("Normal");
        emit snakeSpeed(150);
        break;
    case NORMAL:
        speed = FAST;
        ui->SSL->setText("Fast");
        emit snakeSpeed(100);
        break;
    case FAST:
        break;
    }
}

void Settings::on_SSLB_clicked()
{
    switch(speed)
    {
    case SLOW:
        break;
    case NORMAL:
        speed = SLOW;
        ui->SSL->setText("Slow");
        emit snakeSpeed(200);
        break;
    case FAST:
        speed = NORMAL;
        ui->SSL->setText("Normal");
        emit snakeSpeed(150);
        break;
    }
}

void Settings::on_WRB_clicked()
{
    switch(walls)
    {
    case ENABLED:
        walls = DISABLED;
        ui->WL->setText("Disabled");
        emit wallsEnabled(false);
        break;
    case DISABLED:
        walls = ENABLED;
        ui->WL->setText("Enabled");
        emit wallsEnabled(true);
        break;
    }
}

void Settings::on_WLB_clicked()
{
    switch(walls)
    {
    case ENABLED:
        walls = DISABLED;
        ui->WL->setText("Disabled");
        emit wallsEnabled(false);
        break;
    case DISABLED:
        walls = ENABLED;
        ui->WL->setText("Enabled");
        emit wallsEnabled(true);
        break;
    }
}

void Settings::on_P1LE_textChanged(const QString &arg1)
{
    emit P1Name(arg1);
    ui->P1Name->setText(arg1);
    ui->P1SCB->setText(arg1 + "'s snake color");
}

void Settings::on_P2LE_textChanged(const QString &arg1)
{
    emit P2Name(arg1);
    ui->P2Name->setText(arg1);
    ui->P2SCB->setText(arg1 + "'s snake color");
}

void Settings::on_P1SCB_clicked()
{
    PC[1] = QColorDialog::getColor(Qt::darkGray,this,"Choose Snake Color!");
    if(PC[1].isValid()){
        emit P1Brush(PC[1]);
        CreateExamples(1);
    }
}

void Settings::on_P2SCB_clicked()
{
    PC[2] = QColorDialog::getColor(Qt::cyan,this,"Choose Snake Color!");
    if(PC[2].isValid()){
        emit P2Brush(PC[2]);
        CreateExamples(2);
    }
}

void Settings::CreateExamples(int i){
    SceneP[i]->clear();
    QBrush Brush;
    QPen Pen;
    Brush.setStyle(Qt::SolidPattern);
    Brush.setColor(PC[i]);
    Pen.setColor(QColor(164, 175, 141));
    Pen.setWidthF(0.6);
    ExampleHead = new QGraphicsRectItem;
    ExampleHead->setRect(40,120,20,20);
    ExampleHead->setBrush(Brush);
    ExampleHead->setPen(Pen);
    SceneP[i]->addItem(ExampleHead);
    PC[i].setHsv(PC[i].hsvHue()+20,PC[i].hsvSaturation()-10,PC[i].value());
    Brush.setColor(PC[i]);
    for(int x=60;x<140;x+=20){
    ExampleBody = new QGraphicsRectItem;
    ExampleBody->setRect(x,120,20,20);
    ExampleBody->setBrush(Brush);
    ExampleBody->setPen(Pen);
    SceneP[i]->addItem(ExampleBody);
    }

}

void Settings::on_E2PL_clicked()
{
    switch(eating)
    {
    case ENABLED:
        eating = DISABLED;
        ui->EL->setText("Disabled");
        emit wallsEnabled(false);
        break;
    case DISABLED:
        eating = ENABLED;
        ui->EL->setText("Enabled");
        emit wallsEnabled(true);
        break;
    }
}

void Settings::on_E2PR_clicked()
{
    switch(eating)
    {
    case ENABLED:
        eating = DISABLED;
        ui->EL->setText("Disabled");
        emit eatingEnabled(false);
        break;
    case DISABLED:
        eating = ENABLED;
        ui->EL->setText("Enabled");
        emit eatingEnabled(true);
        break;
    }
}
