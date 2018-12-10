#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include "game.h"

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
    QLabel *label[15];
    virtual void keyPressEvent(QKeyEvent* event);
private slots:
    void updateBoard(QList<Block>);
};



#endif // MAINWINDOW_H
