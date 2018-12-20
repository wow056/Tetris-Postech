#ifndef DIALOG_GAMEOVER_H
#define DIALOG_GAMEOVER_H

#include <QDialog>
#include <QFont>
#include <QFontDatabase>

namespace Ui {
class Dialog_gameOver;
}

class Dialog_gameOver : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_gameOver(int score, QWidget *parent = nullptr);
    ~Dialog_gameOver();
private:
    Ui::Dialog_gameOver *ui;
};

#endif // DIALOG_GAMEOVER_H
