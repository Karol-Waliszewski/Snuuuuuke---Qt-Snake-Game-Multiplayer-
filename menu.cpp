#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setMouseTracking(true);
    this->setObjectName("Background");
    this->setStyleSheet("#Background{background-image: url(:/menu/img/ALLGAMEBG.png);};");

    Logo = new QPixmap(":/menu/img/logo.png");
    HowToPlay = new QPixmap(":/menu/img/HOW TO PLAY.png");
    Credits = new QPixmap(":/menu/img/credits.png");

    setLogo();

    connect(ui->HTPButton,SIGNAL(HowToPlay()),this,SLOT(setHowToPlay()));
    connect(ui->HTPButton,SIGNAL(Logo()),this,SLOT(setLogo()));

    connect(ui->creditsButton,SIGNAL(Credits()),this,SLOT(setCredits()));
    connect(ui->creditsButton,SIGNAL(Logo()),this,SLOT(setLogo()));
}

Menu::~Menu()
{
    delete ui;
}

void Menu::setLogo()
{
    ui->logoLabel->setPixmap(Logo->scaled(550,550,Qt::KeepAspectRatio));
}

void Menu::setHowToPlay()
{
    ui->logoLabel->setPixmap(HowToPlay->scaled(550,550,Qt::KeepAspectRatio));
}

void Menu::setCredits()
{
    ui->logoLabel->setPixmap(Credits->scaled(550,550,Qt::KeepAspectRatio));
}

void Menu::paintEvent(QPaintEvent *pe){
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void Menu::on_quitButton_clicked()
{
    qApp->quit();
}

void Menu::on_spButton_clicked()
{
    currWindow(2); // 2 = SINGLEPLAYER
}

void Menu::on_mpButton_clicked()
{
    currWindow(3); // 3 = MULTIPLAYER
}

void Menu::on_settingsButton_clicked()
{
    currWindow(1); // 1 = SETTINGS
}


void Menu::on_HTPButton_clicked()
{
   //
}

void Menu::on_creditsButton_clicked()
{

}
