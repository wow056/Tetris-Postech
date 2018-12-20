#include "dialog_select.h"
#include "ui_dialog_select.h"
#include "game.h"

dialog_select::dialog_select(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_select)
{
    ui->setupUi(this);

	QFontDatabase::addApplicationFont(":/font/aerial.ttf");
	QFont aerial("aerial", 12, QFont::Normal);

	ui->label->setFont(aerial);
	ui->label_2->setFont(aerial);
	ui->label_3->setFont(aerial);
}

dialog_select::~dialog_select()
{
    delete ui;
}

void dialog_select::on_normal_btn_clicked()
{
    done(Game::Normal);
}

void dialog_select::on_item_btn_clicked()
{
    done(Game::Item);
}

void dialog_select::on_speed_btn_clicked()
{
    done(Game::Speed);
}
