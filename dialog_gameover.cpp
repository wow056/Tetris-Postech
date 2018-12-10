#include "dialog_gameover.h"
#include "ui_dialog_gameover.h"

Dialog_gameOver::Dialog_gameOver(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_gameOver)
{
    ui->setupUi(this);
}

Dialog_gameOver::~Dialog_gameOver()
{
    delete ui;
}

void Dialog_gameOver::show_score(int score)
{
    QString txt;
    txt="Score : ";
    txt+=QString::number(score);
    ui->label_showScore->setText(txt);
}
