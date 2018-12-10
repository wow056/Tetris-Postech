#include "block.h"


Piece::Piece(int shape, int color)
	:_shape(shape)
	,_color(color)
	,_pos(middle_x , -1)
{
	switch (_shape)
	{
	case Piece::SHAPE_I:
		_blocks[0] = Coordinate(0,-2);
		_blocks[1] = Coordinate(0,-1);
		_blocks[2] = Coordinate(0,0);
		_blocks[3] = Coordinate(0,1);
		break;
	case Piece::SHAPE_O:
		_blocks[0] = Coordinate(0, 0);
		_blocks[1] = Coordinate(1, 0);
		_blocks[2] = Coordinate(0, 1);
		_blocks[3] = Coordinate(1, 1);
		break;
	case Piece::SHAPE_Z:
		_blocks[0] = Coordinate(-1, 0);
		_blocks[1] = Coordinate(0, 0);
		_blocks[2] = Coordinate(0, 1);
		_blocks[3] = Coordinate(1, 1);
		break;
	case Piece::SHAPE_S:
		_blocks[0] = Coordinate(-1, 1);
		_blocks[1] = Coordinate(0, 1);
		_blocks[2] = Coordinate(0, 0);
		_blocks[3] = Coordinate(1, 1);
		break;
	case Piece::SHAPE_J:
		_blocks[0] = Coordinate(0, -1);
		_blocks[1] = Coordinate(0, 0);
		_blocks[2] = Coordinate(0, 1);
		_blocks[3] = Coordinate(1, 1);
		break;
	case Piece::SHAPE_L:
		_blocks[0] = Coordinate(0, -1);
		_blocks[1] = Coordinate(0, 0);
		_blocks[2] = Coordinate(0, 1);
		_blocks[3] = Coordinate(-1, 1);
		break;
	case Piece::SHAPE_T:
		_blocks[0] = Coordinate(-1, 0);
		_blocks[1] = Coordinate(0, 0);
		_blocks[2] = Coordinate(1, 0);
		_blocks[3] = Coordinate(0, 1);
		break;
	}
}

void Piece::rotate(int direction)
{
	int temp;
	switch (direction)
	{
	case CW:
		for (int i = 0; i < 4; i++)
		{
			temp = _blocks[i].x;
			_blocks[i].x = _blocks[i].y;
			_blocks[i].y = -temp;
		}
		break;
	case CCW:
		for (int i = 0; i < 4; i++)
		{
			temp = _blocks[i].x;
			_blocks[i].x = -_blocks[i].y;
			_blocks[i].y = temp;
		}
		break;
	}
}

void Piece::left()
{
	_pos.x--;
}

void Piece::right()
{
	_pos.x++;
}

void Piece::down()
{
	_pos.y++;
}

bool Piece::isOverlapped(Coordinate block_pos)
{
	for (int i = 0; i < 4; i++)
	{
		if ((_pos + _blocks[i]) == block_pos)
			return true;
	}
	return false;
}

QList<Block> Piece::blocks()
{
	QList<Block> b_list;
	for (int i = 0; i < 4; i++)
	{
		Block b;
		b.color = _color;
		b.pos = _pos + _blocks[i];
		b_list << b;
	}
	return b_list;
}
