#include "dialog_gameover.h"
#include "ui_dialog_gameover.h"
#include <QStyle>

Dialog_gameOver::Dialog_gameOver(int score, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_gameOver)
{
    ui->setupUi(this);
	QFontDatabase::addApplicationFont(":/font/aerial.ttf");
	QFont aerial("aerial", 15, QFont::Normal);
	ui->label->setFont(aerial);
	ui->label_showScore->setFont(aerial);
	ui->label_3->setFont(aerial);
	ui->label_showScore->setText(tr("<font color='white'>Score: ") + QString::number(score));
}

Dialog_gameOver::~Dialog_gameOver()
{
    delete ui;
}
