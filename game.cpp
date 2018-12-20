#include "game.h"

const Coordinate Game::board_size = Coordinate(GAME_WIDTH, GAME_HEIGHT);
const float Game::SpeedIncrement = 0.001;

Game::Game(int mode, QObject *parent)
	:QObject(parent), mode(mode),
	timer_interbal(600),
	total_score(0)
{
	setNextPiece();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(timer_interbal);
	if (mode == Speed)
	{
		timer_speedmode = new QTimer(this);
		connect(timer_speedmode, SIGNAL(timeout()), this, SLOT(updateSpeed()));
		timer_speedmode->start(600);
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
        if(isGameover())
        {
			timer->stop();
			deleteLater();
            emit gameOver(total_score);
			return;
        }

        setNextPiece();
	}
	while((deleteLineIndex = findCompleteLine()) >= 0)
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
    int itemEffect=0;
	auto it = savedBlocks.begin();
	while (it != savedBlocks.end())
	{
		if (it->pos.y == line_index)
		{
            if(it->iamitem==1)
            {
                itemEffect=1;
            }
			it = savedBlocks.erase(it);
		}
		else
		{
			it++;
		}
	}
	for (it = savedBlocks.begin(); it != savedBlocks.end(); it++)
	{
		if (it->pos.y < line_index)
			it->pos.y++;
	}
    increaseScore(100);
    //item effect delete bottom one line;
    if(itemEffect==1)
    {
            it = savedBlocks.begin();
            while (it != savedBlocks.end())
            {
                if (it->pos.y == 20)
                {
                    it = savedBlocks.erase(it);
                }
                else
                {
                    it++;
                }
            }
            for (it = savedBlocks.begin(); it != savedBlocks.end(); it++)
            {
                if (it->pos.y < 30)
                    it->pos.y++;
            }
    itemEffect=0;
    }
	putOutput();
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
	nextPiece = Piece();
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
