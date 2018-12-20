#include "dialog_select.h"
#include "ui_dialog_select.h"
#include "game.h"

dialog_select::dialog_select(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_select)
{
    ui->setupUi(this);
}

dialog_select::~dialog_select()
{
    delete ui;
}

void dialog_select::on_normalButton_clicked()
{
    done(Game::Normal);
}

void dialog_select::on_itemButton_clicked()
{
    done(Game::Item);
}

void dialog_select::on_speedButton_clicked()
{
    done(Game::Speed);
}
