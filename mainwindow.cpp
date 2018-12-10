#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	QVBoxLayout *layout = new QVBoxLayout(this);
	centralWidget()->setLayout(layout);
    for (int i = 0; i < 15; i++)
	{
		label[i] = new QLabel(this);
		layout->addWidget(label[i]);
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

void MainWindow::updateBoard(QList<Block> l)
{
	std::sort(l.begin(), l.end());
    qDebug() << "updated main window";
    auto it = l.begin();
	for (int y = 0; y < Game::board_size.y; y++)
	{
		QString s;
		for (int x = 0; x < Game::board_size.x; x++)
		{
            if (it == l.end())
            {
                s.append(QString::fromUtf8("\u25A1"));
            }
            else if (x == it->pos.x && y == it->pos.y)
			{
                qDebug() << "printed on(" <<x <<", " << y<<")";
                s.append(QString::fromUtf8("\u25A0"));
				it++;
			}
			else
			{
                while(it != l.end()&& it->pos.y < 0)
                    it++;
                s.append(QString::fromUtf8("\u25A1"));
			}
		}
		label[y]->setText(s);
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
