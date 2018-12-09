#include "game.h"



Game::Game(QObject *parent = nullptr)
	:QObject(parent),
	nextPiece(0, 0), currentPiece(0, 0)
{
	timer = new QTimer(this);
	timer_interbal = 1000;

	//timer_interbal 시간이 지날 때마다 update 함수가 실행됨.
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(timer_interbal);
}



void Game::setInput(int input)
{
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
}

void Game::update()
{
	if (isBlockDrop())
		setBlockDrop();
	if (isLineComplete())
		deleteLine();
}
