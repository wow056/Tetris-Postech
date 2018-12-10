#include "game.h"



Game::Game(QObject *parent = nullptr)
	:QObject(parent),
	nextPiece(0, 0), currentPiece(0, 0)
{
	qDebug() << "entering:	Game::Game";
	timer = new QTimer(this);
	timer_interbal = 1000;

	//timer_interbal 시간이 지날 때마다 update 함수가 실행됨.
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(timer_interbal);
	qDebug() << "exiting:	Game::Game";
}



void Game::setInput(int input)
{
	qDebug() << "entering:	Game::setInput";
	switch (input)
	{
	case Qt::Key_Left:
		if (isBlockMove(LEFT))
			setBlockMove(LEFT);
		break;
	case Qt::Key_Right:
		if (isBlockMove(RIGHT))
			setBlockMove(RIGHT);
		break;
	case Qt::Key_Up:
		if (isBlockRotate(LEFT))
			setBlockRotate(LEFT);
		break;
	case Qt::Key_Down:
		if (isBlockRotate(RIGHT))
			setBlockRotate(RIGHT);
		break;
	}
	qDebug() << "entering:	Game::setInput";
}

void Game::update()
{
	qDebug() << "entering:	Game::update";
	if (isBlockDrop())
		setBlockDrop();
	if (isLineComplete())
		deleteLine();
	qDebug() << "exiting:	Game::update";
}

bool Game::isGameover() const
{
	return false;
}

bool Game::isBlockDrop() const
{
	return false;
}

bool Game::isBlockMove(int direction) const
{
	return false;
}

bool Game::isBlockRotate(int direction) const
{
	return false;
}

bool Game::isBlockEnd() const
{
	return false;
}

bool Game::isLineComplete() const
{
	return false;
}

void Game::deleteLine()
{
	qDebug() << "entering:	Game::deleteLine";
	putOutput();
	qDebug() << "exiting:	Game::deleteLine";
}

void Game::setBlockDrop()
{
	qDebug() << "entering:	Game::setBlockDrop";
	putOutput();
	qDebug() << "exiting:	Game::setBlockDrop";
}

void Game::setBlockMove(int direction)
{
	qDebug() << "entering:	Game::setBlockMove";
	putOutput();
	qDebug() << "exiting:	Game::setBlockDrop";
}

void Game::setBlockRotate(int direction)
{
	qDebug() << "entering:	Game::setBlockRotate";
	putOutput();
	qDebug() << "exiting:	Game::setBlockRotate";
}

void Game::saveBlock()
{
	qDebug() << "entering:	Game::saveBlock";
	putOutput();
	qDebug() << "exiting:	Game::saveBlock";
}

void Game::setNextPiece()
{
	qDebug() << "entering:	Game::setNextPiece";
	emit sendNextBlock(nextPiece);
	qDebug() << "exiting:	Game::setNextPiece";
}

void Game::putOutput()
{
	QList<Block> output;
	qDebug() << "entering:	Game::putOutput";
	output = savedBlocks + currentPiece.blocks();
	emit updateBoard(output);
	qDebug() << "exiting:	Game::putOutput";
}
