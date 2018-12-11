#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include "game.h"
#include "dialog_gameover.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Game *game;
    QLabel *label[GAME_HEIGHT];
    virtual void keyPressEvent(QKeyEvent* event);
    Dialog_gameOver *dialog_gameOver;

private slots:
    void updateBoard(QList<Block>);
    void gameOver(int total_score);
};



#endif // MAINWINDOW_H
