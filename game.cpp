#include "game.h"

const Coordinate Game::board_size = Coordinate(20, 50);

Game::Game(QObject *parent)
	:QObject(parent),
    nextPiece(), currentPiece()
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
	int deleteLineIndex;
	qDebug() << "entering:	Game::update";
    putOutput(); // 테스트용,곧 지울 예정입니다
	if (isBlockDroppable())
		setBlockDrop();
	else
		saveBlock();
	deleteLineIndex = findCompleteLine();
	if (deleteLineIndex >= 0)
		deleteLine(deleteLineIndex);
	qDebug() << "exiting:	Game::update";
}

bool Game::isGameover() const
{
	return false;
}

bool Game::isBlockDroppable() const
{
	Piece tester = currentPiece;
	tester.down();
	for (auto it = savedBlocks.begin(); it != savedBlocks.end(); it++)
	{
		if (tester.isOverlapped(it->pos))
			return false;
	}
	if (tester.isOverlapped(0, Piece::X_COORDINATE))
	{
		return false;
	}
	if (tester.isOverlapped(board_size.x, Piece::X_COORDINATE))
	{
		return false;
	}
	if (tester.isOverlapped(board_size.y, Piece::Y_COORDINATE))
	{
		return false;
	}

	return true;
}

bool Game::isBlockMove(int direction) const
{
	Piece tester = currentPiece;
	switch (direction)
	{
	case Piece::LEFT:
		tester.left();
		break;
	case Piece::RIGHT:
		tester.right();
		break;
	}

	for (auto it = savedBlocks.begin(); it != savedBlocks.end(); it++)
	{
		if (tester.isOverlapped(it->pos))
			return false;
	}
	if (tester.isOverlapped(0, Piece::X_COORDINATE))
	{
		return false;
	}
	if (tester.isOverlapped(board_size.x, Piece::X_COORDINATE))
	{
		return false;
	}

	return true;
}

bool Game::isBlockRotate(int direction) const
{
	Piece tester = currentPiece;
	switch (direction)
	{
	case Piece::CCW:
		tester.rotate(Piece::CCW);
		break;
	case Piece::CW:
		tester.rotate(Piece::CW);
		break;
	}
	for (auto it = savedBlocks.begin(); it != savedBlocks.end(); it++)
	{
		if (tester.isOverlapped(it->pos))
			return false;
	}
	if (tester.isOverlapped(0, Piece::X_COORDINATE))
	{
		return false;
	}
	if (tester.isOverlapped(board_size.x, Piece::X_COORDINATE))
	{
		return false;
	}
	if (tester.isOverlapped(board_size.y, Piece::Y_COORDINATE))
	{
		return false;
	}

	return true;
}

int Game::findCompleteLine() const
{
	int i, j;
	for (i = 0; i < board_size.y; i++)
	{
		for (j = 1; j < board_size.x; j++)
		{
			Block finder;
			finder.pos.y = i;
			finder.pos.x = j;
			if (savedBlocks.count(finder) == 0)
				break;
		}
		if (j == board_size.x)
			return i;
	}
	return -1;
}

void Game::deleteLine(int line_index)
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
