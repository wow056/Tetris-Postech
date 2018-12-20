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
    //QLabel *label[GAME_HEIGHT];
    QLabel* labels[10][20];
    QLabel* nextname;
    QLabel* scorename;
    QLabel* speedname;
    QLabel* scoretext;
    QLabel* speedtext;
    QLabel* nextboard;
    QLabel* scoreboard;
    QLabel* speedboard;
    QLabel* mark;
    QLabel* gamemode;

    virtual void keyPressEvent(QKeyEvent* event);
    Dialog_gameOver *dialog_gameOver;
    QPixmap blue;
    QPixmap back;
    QPixmap green;
    QPixmap orange;
    QPixmap pink;
    QPixmap red;
    QPixmap sky;
    QPixmap yellow;
    QPixmap Next;
    QPixmap blueNext;
    QPixmap greenNext;
    QPixmap orangeNext;
    QPixmap pinkNext;
    QPixmap redNext;
    QPixmap skyNext;
    QPixmap yellowNext;
    QPixmap tetrismark;

private slots:
    void updateBoard(QList<Block>);
    void gameOver(int total_score);
    QPixmap blockcolor(int);
    void showNextBlock(int);
    void showScore(int);
};



#endif // MAINWINDOW_H
