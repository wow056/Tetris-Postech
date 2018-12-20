#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <QGridLayout>
#include <QWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QVBoxLayout *layout = new QVBoxLayout(this);
    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    centralWidget()->setLayout(layout);

    QFont font("NanumSquareEB", 15);
    test = new QLabel(centralWidget());
    test->move(20, 350);
    test->setFont(font);
    test->setText("SCORE");

    blue=QPixmap(":/block/blue.png");
    back=QPixmap(":/block/back.png");
    green=QPixmap(":/block/green.png");
    orange=QPixmap(":/block/orange.png");
    pink=QPixmap(":/block/pink.png");
    red=QPixmap(":/block/red.png");
    sky=QPixmap(":/block/sky.png");
    yellow=QPixmap(":/block/yellow.png");

    for(int i=0; i<10; i++)
    {
        for(int j=0; j<20; j++)
        {
            labels[i][j] = new QLabel(centralWidget());
            labels[i][j]->move(20+i*30, 20+j*30);
            labels[i][j]->setFixedWidth(30);
            labels[i][j]->setFixedHeight(30);
            //layout->addWidget(labels[i][j], i, j);
            //labels[i][j]->setPixmap(blue);
        }
    }
    game = new Game(this);
    connect(game, SIGNAL(updateBoard(QList<Block>)), this, SLOT(updateBoard(QList<Block>)));
    connect(game, SIGNAL(gameOver(int)),this,SLOT(gameOver(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    game->setInput(event->key());
}

QPixmap MainWindow::blockcolor(int n)
{
    switch(n)
    {
    case 1:
        return red;
    case 2:
        return orange;
    case 3:
        return green;
    case 4:
        return pink;
    case 5:
        return sky;
    case 6:
        return yellow;
    case 7:
        return blue;
    }
}

void MainWindow::updateBoard(QList<Block> l)
{
    std::sort(l.begin(), l.end());
    qDebug() << "updated main window";
    auto it = l.begin();

    for (int y = 0; y < Game::board_size.y; y++)
	{
        //QString s;
        for (int x = 0; x < Game::board_size.x; x++)
		{
            if (it == l.end())
            {
                //s.append(QString::fromUtf8("\u25A1"));
                labels[x][y]->setPixmap(back);
            }
            else if (x == it->pos.x && y == it->pos.y)
			{
                qDebug() << "printed on(" <<x <<", " << y<<")";
                //s.append(QString::fromUtf8("\u25A0"));
                labels[x][y]->setPixmap(blockcolor(it->color));
				it++;
			}
			else
			{
                while(it != l.end()&& it->pos.y < 0)
                    it++;
                labels[x][y]->setPixmap(back);
                //s.append(QString::fromUtf8("\u25A1"));
            }
        }
        //label[y]->setText(s);
	}

//	for (auto it = l.begin(); it != l.end(); it++)
//	{
//		qDebug() << '(' << it->pos.x << ", " << it->pos.y << ") color: ", it->color;
//	}
}
void MainWindow::gameOver(int score)
{
    dialog_gameOver = new Dialog_gameOver(this);
    dialog_gameOver->show_score(score);
    dialog_gameOver->exec();

}
