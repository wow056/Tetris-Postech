#ifndef DIALOG_GAMEOVER_H
#define DIALOG_GAMEOVER_H

#include <QDialog>

namespace Ui {
class Dialog_gameOver;
}

class Dialog_gameOver : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_gameOver(QWidget *parent = nullptr);
    ~Dialog_gameOver();
    void show_score(int);

private:
    Ui::Dialog_gameOver *ui;
};

#endif // DIALOG_GAMEOVER_H
