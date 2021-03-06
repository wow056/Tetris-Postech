#include "game.h"

const Coordinate Game::board_size = Coordinate(GAME_WIDTH, GAME_HEIGHT);
const float Game::SpeedIncrement = 100;

Game::Game(int mode, QObject *parent)
	:QObject(parent), mode(mode),
	timer_interbal(600),
	total_score(0)
{
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(timer_interbal);
	if (mode == Speed)
	{
		timer_speedmode = new QTimer(this);
		connect(timer_speedmode, SIGNAL(timeout()), this, SLOT(updateSpeed()));
		timer_speedmode->start(600);
	}
	switch (mode)
	{
	case Speed:
	{
		timer_speedmode = new QTimer(this);
		connect(timer_speedmode, SIGNAL(timeout()), this, SLOT(updateSpeed()));
		timer_speedmode->start(600);
		break;
	}
	case Item:
	{
		currentPiece = Piece(true);
		setNextPiece();
		break;
	}
	default:
		break;
	}
}



void Game::setInput(int input)
{
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
		if (isBlockRotate(Piece::CCW))
			setBlockRotate(Piece::CCW);
		break;
	case Qt::Key_Down://go down
		if (isBlockDroppable())
			setBlockDrop();
		break;
	case Qt::Key_Space://go fastly down
		while (isBlockDroppable())
			setBlockDrop();
		update();
		break;
	}
}

void Game::update()
{
	int deleteLineIndex;
	if (isBlockDroppable())
	{
		setBlockDrop();
	}
	else
	{
		saveBlock();
		if (isGameover())
		{
			timer->stop();
			if (mode == Speed)
				timer_speedmode->stop();
			emit gameOver(total_score);
			return;
		}
		setNextPiece();
	}
	while ((deleteLineIndex = findCompleteLine()) >= 0)
		deleteLine(deleteLineIndex);
}

void Game::updateSpeed()
{
	int interval = timer->interval();
	float speed = 100000.0 / interval;
	speed += SpeedIncrement;
	timer->setInterval(100000 / speed);
	emit updatedSpeed(speed);
}

void Game::restartSignals()
{
	blockSignals(false);
	timer->start();
	pause_timer->deleteLater();
}

bool Game::isGameover() const
{
	//Check whether the Game is over or not
	for (auto it = savedBlocks.begin(); it != savedBlocks.end(); it++)
	{
		if (it->pos.y < 0)
		{
			return true;
		}
	}
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
	if (tester.isOverlapped(-1, Piece::X_COORDINATE))
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
	if (tester.isOverlapped(-1, Piece::X_COORDINATE))
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
		for (j = 0; j < board_size.x; j++)
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
	bool itemEffect = false;
    bool bombEffect = false;
	auto it = savedBlocks.begin();
    QList<Coordinate> bomb_posList;
	while (it != savedBlocks.end())
	{
		if (it->pos.y == line_index)
		{
			if (it->isitem)
				itemEffect = true;
            if(it->isbomb)
            {
                bomb_posList << it->pos;
                bombEffect=true;
            }
			it = savedBlocks.erase(it);
		}
		else
		{
			it++;
		}
	}
	for (auto it = savedBlocks.begin(); it != savedBlocks.end(); it++)
		if (it->pos.y < line_index)
			it->pos.y++;
	increaseScore(100);
	putOutput();
	//item effect delete bottom one line;
	if (itemEffect)
	{
		it = savedBlocks.begin();
		while (it != savedBlocks.end())
		{
			if (it->pos.y == board_size.y)
				it = savedBlocks.erase(it);
			else
				it++;
		}
		increaseScore(100);
		putOutput();

		for (auto it = savedBlocks.begin(); it != savedBlocks.end(); it++)
			if (it->pos.y < board_size.y)
			{
				it->pos.y++;
			}
		pause_timer = new QTimer();
		blockSignals(true);
		timer->stop();
		pause_timer->singleShot(500, this, SLOT(restartSignals()));
	}
    else if(bombEffect)
    {
        for(auto it1 = bomb_posList.begin();it1 != bomb_posList.end(); it1++){
           Coordinate bomb_pos = *it1;
        it = savedBlocks.begin();
        while (it != savedBlocks.end())
        {
            if(it->pos.x==bomb_pos.x-1&&it->pos.y==bomb_pos.y-1)
                it = savedBlocks.erase(it);
            else if(it->pos.x==bomb_pos.x&&it->pos.y==bomb_pos.y-1)
                it = savedBlocks.erase(it);
            else if(it->pos.x==bomb_pos.x+1&&it->pos.y==bomb_pos.y-1)
                it = savedBlocks.erase(it);
            else if(it->pos.x==bomb_pos.x-1&&it->pos.y==bomb_pos.y+1)
                it = savedBlocks.erase(it);
            else if(it->pos.x==bomb_pos.x&&it->pos.y==bomb_pos.y+1)
                it = savedBlocks.erase(it);
            else if(it->pos.x==bomb_pos.x+1&&it->pos.y==bomb_pos.y+1)
                it = savedBlocks.erase(it);
            else
                it++;
			putOutput();
        }
        for (auto it = savedBlocks.begin(); it != savedBlocks.end(); it++){
            if (it->pos.x==bomb_pos.x-1 ||it->pos.x==bomb_pos.x||it->pos.x==bomb_pos.x+1)
            {
                if(it->pos.y<bomb_pos.y+2)
				{
					it->pos.y++;
				}
            }
        }
        }
		pause_timer = new QTimer();
		blockSignals(true);
		timer->stop();
		pause_timer->singleShot(500, this, SLOT(restartSignals()));
    }
	else {
		putOutput();
	}
}

void Game::setBlockDrop()
{
	currentPiece.down();
	putOutput();
}

void Game::setBlockMove(int direction)
{
	switch (direction)
	{
	case Piece::RIGHT:
		currentPiece.right();
		break;
	case Piece::LEFT:
		currentPiece.left();
		break;
	}
	putOutput();
}

void Game::setBlockRotate(int direction)
{
	switch (direction)
	{
	case Piece::CW:
		currentPiece.rotate(Piece::CW);
		break;
	case Piece::CCW:
		currentPiece.rotate(Piece::CCW);
		break;
	}
	putOutput();
}

void Game::saveBlock()
{
	savedBlocks += currentPiece.blocks();
	currentPiece = nextPiece;
	putOutput();
}

void Game::setNextPiece()
{
	nextPiece = Piece(mode == Item);
	emit updateNextPiece(nextPiece.shape());
}

void Game::putOutput()
{
	QList<Block> output;
	output = savedBlocks + currentPiece.blocks();
	emit updateBoard(output);
}

void Game::increaseScore(int n)
{
	total_score += n;
	updatedScore(total_score);
}
