#include "game.h"



Game::Game(QObject *parent)
	:QObject(parent),
    nextPiece(), currentPiece()
{
	qDebug() << "entering:	Game::Game";
	timer = new QTimer(this);
	timer_interbal = 1000;

	//timer_interbal �ð��� ���� ������ update �Լ��� �����.
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
		if (isBlockMove(Piece::LEFT))
			setBlockMove(Piece::LEFT);
		break;
	case Qt::Key_Right:
		if (isBlockMove(Piece::RIGHT))
			setBlockMove(Piece::RIGHT);
		break;
	case Qt::Key_Up:
		if (isBlockRotate(Piece::LEFT))
			setBlockRotate(Piece::LEFT);
		break;
	case Qt::Key_Down:
		if (isBlockRotate(Piece::RIGHT))
			setBlockRotate(Piece::RIGHT);
		break;
	}
	qDebug() << "entering:	Game::setInput";
}

void Game::update()
{
	qDebug() << "entering:	Game::update";
    putOutput(); // �׽�Ʈ��,�� ���� �����Դϴ�
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
