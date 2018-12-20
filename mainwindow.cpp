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

    special=QPixmap(":/block/special.png");
    blue=QPixmap(":/block/blue.png");
    back=QPixmap(":/block/back.png");
    green=QPixmap(":/block/green.png");
    orange=QPixmap(":/block/orange.png");
    pink=QPixmap(":/block/pink.png");
    red=QPixmap(":/block/red.png");
    sky=QPixmap(":/block/sky.png");
    yellow=QPixmap(":/block/yellow.png");
    blueNext=QPixmap(":/block/blueNext.png");
    Next=QPixmap(":/block/Next.png");
    greenNext=QPixmap(":/block/greenNext.png");
    orangeNext=QPixmap(":/block/orangeNext.png");
    pinkNext=QPixmap(":/block/pinkNext.png");
    redNext=QPixmap(":/block/redNext.png");
    skyNext=QPixmap(":/block/skyNext.png");
    yellowNext=QPixmap(":/block/yellowNext.png");
    tetrismark=QPixmap(":/block/tetrismark.png");


    QFontDatabase::addApplicationFont(":/font/aerial.ttf");

    QFont aerial("aerial", 15, QFont::Normal);
    QFont aeriall("aerial", 30, QFont::Normal);

    gamemode = new QLabel(centralWidget());
    gamemode->move(35, 30);
    gamemode->setFont(aerial);
    gamemode->setText("<font color='white'>NORMAL");

    nextname = new QLabel(centralWidget());
    nextname->move(350, 29);
    nextname->setFont(aerial);
    nextname->setText("<font color='white'>NEXT");

    scorename = new QLabel(centralWidget());
    scorename->move(350, 199);
    scorename->setFont(aerial);
    scorename->setText("<font color='white'>SCORE");

    speedname = new QLabel(centralWidget());
    speedname->move(350, 369);
    speedname->setFont(aerial);
    speedname->setText("<font color='white'>SPEED");

    nextboard = new QLabel(centralWidget());
    nextboard->move(345, 60);
    nextboard->setPixmap(Next);

    scoreboard = new QLabel(centralWidget());
    scoreboard->move(345, 230);
    scoreboard->setPixmap(Next);

    speedboard = new QLabel(centralWidget());
    speedboard->move(345, 400);
    speedboard->setPixmap(Next);

    mark = new QLabel(centralWidget());
    mark->move(345, 550);
    mark->setPixmap(tetrismark);

    scoretext = new QLabel(centralWidget());
    scoretext->move(380, 260);
    scoretext->setFont(aeriall);
    scoretext->setStyleSheet("color: white; background: rgb(49, 54, 59);");
    scoretext->setFixedWidth(120);
    scoretext->setText("0");
    scoretext->setAlignment(Qt::AlignCenter);



    for(int i=0; i<10; i++)
    {
        for(int j=0; j<20; j++)
        {
            labels[i][j] = new QLabel(centralWidget());
            labels[i][j]->move(30+i*30, 60+j*30);
            labels[i][j]->setFixedWidth(30);
            labels[i][j]->setFixedHeight(30);
        }
    }
    game = new Game(this);
    connect(game, SIGNAL(updateBoard(QList<Block>)), this, SLOT(updateBoard(QList<Block>)));
    connect(game, SIGNAL(gameOver(int)),this,SLOT(gameOver(int)));
    connect(game, SIGNAL(updateNextPiece(int)), this, SLOT(showNextBlock(int)));
    connect(game, SIGNAL(updatedScore(int)), this, SLOT(showScore(int)));
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
    case 0:
        return special;
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

void MainWindow::showNextBlock(int n)
{
    switch(n)
    {
    case 0:
        nextboard->setPixmap(redNext);
        break;
    case 1:
        nextboard->setPixmap(orangeNext);
        break;
    case 2:
        nextboard->setPixmap(greenNext);
        break;
    case 3:
        nextboard->setPixmap(pinkNext);
        break;
    case 4:
        nextboard->setPixmap(skyNext);
        break;
    case 5:
        nextboard->setPixmap(yellowNext);
        break;
    case 6:
        nextboard->setPixmap(blueNext);
        break;
    default:
        nextboard->setPixmap(Next);
        break;
    }
    return;
}

void MainWindow::showScore(int n)
{
    scoretext->setText(QString::number(n));
    return;
}

void MainWindow::gameOver(int score)
{
    dialog_gameOver = new Dialog_gameOver(this);
    dialog_gameOver->show_score(score);
	if (dialog_gameOver->exec() == QDialog::Accepted)
	{
		disconnect(game);
		delete game;
		game = new Game();
		connect(game, SIGNAL(updateBoard(QList<Block>)), this, SLOT(updateBoard(QList<Block>)));
		connect(game, SIGNAL(gameOver(int)), this, SLOT(gameOver(int)));
	}
	else  
	{
		
	}

}
