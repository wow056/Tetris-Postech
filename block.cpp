#include "block.h"

Piece::Piece()
{
	_shape = qrand() % 7;
	_pos = Coordinate(middle_x, -1);
	setRotation(0);
}

int Piece::shape()
{
	return _shape;
}

void Piece::rotate(int direction)
{
	int temp;
	switch (direction)
	{
	case CW:
		temp = _rotation - 1;
		if (temp < 0)
			temp = 3;
		setRotation(temp);
		break;
	case CCW:
		temp = _rotation + 1;
		if (temp > 3)
			temp = 0;
		setRotation(temp);
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

bool Piece::isOverlapped(Coordinate block_pos) const
{
	for (int i = 0; i < 4; i++)
	{
		if ((_pos + _blocks[i]) == block_pos)
			return true;
	}
	return false;
}

bool Piece::isOverlapped(int line_pos, int coordinate_type) const
{
	for (int i = 0; i < 4; i++)
	{
		switch (coordinate_type)
		{
		case X_COORDINATE:
			if (_pos.x + _blocks[i].x == line_pos)
				return true;
			break;
		case Y_COORDINATE:
			if (_pos.y + _blocks[i].y == line_pos)
				return true;
			break;
		}
	}
	return false;
}

QList<Block> Piece::blocks()
{
	QList<Block> b_list;
	for (int i = 0; i < 4; i++)
	{
		Block b;
		b.color = _shape + 1;
		b.pos = _pos + _blocks[i];
		b_list << b;
	}
	return b_list;
}

void Piece::setRotation(int rotation)
{
	_rotation = rotation;
	switch (_shape)
	{
	case Piece::SHAPE_I:
		switch (_rotation)
		{
		case 0:
		case 2:
			_blocks[0] = Coordinate(0, -2);
			_blocks[1] = Coordinate(0, -1);
			_blocks[2] = Coordinate(0, 0);
			_blocks[3] = Coordinate(0, 1);
			break;
		case 1:
		case 3:
			_blocks[0] = Coordinate(-2, 1);
			_blocks[1] = Coordinate(-1, 1);
			_blocks[2] = Coordinate(0, 1);
			_blocks[3] = Coordinate(1, 1);
			break;
		}
		break;
	case Piece::SHAPE_O:
		_blocks[0] = Coordinate(0, 0);
		_blocks[1] = Coordinate(1, 0);
		_blocks[2] = Coordinate(0, 1);
		_blocks[3] = Coordinate(1, 1);
		break;
	case Piece::SHAPE_Z:
		switch (_rotation)
		{
		case 0:
		case 2:
			_blocks[0] = Coordinate(0, 0);
			_blocks[1] = Coordinate(1, 0);
			_blocks[2] = Coordinate(0, 1);
			_blocks[3] = Coordinate(1, -1);
			break;
		case 1:
		case 3:
			_blocks[0] = Coordinate(-1, 0);
			_blocks[1] = Coordinate(0, 0);
			_blocks[2] = Coordinate(0, 1);
			_blocks[3] = Coordinate(1, 1);
			break;
		}
		break;
	case Piece::SHAPE_S:
		switch (_rotation)
		{
		case 0:
		case 2:
			_blocks[0] = Coordinate(0, 0);
			_blocks[1] = Coordinate(-1, 0);
			_blocks[2] = Coordinate(0, 1);
			_blocks[3] = Coordinate(-1, -1);
			break;
		case 1:
		case 3:
			_blocks[0] = Coordinate(1, 0);
			_blocks[1] = Coordinate(0, 0);
			_blocks[2] = Coordinate(0, 1);
			_blocks[3] = Coordinate(-1, 1);
			break;
		}
		break;
	case Piece::SHAPE_J:
		switch (_rotation)
		{
		case 0:
			_blocks[0] = Coordinate(0, -1);
			_blocks[1] = Coordinate(0, 0);
			_blocks[2] = Coordinate(0, 1);
			_blocks[3] = Coordinate(-1, 1);
			break;
		case 1:
			_blocks[0] = Coordinate(-2, 0);
			_blocks[1] = Coordinate(-1, 0);
			_blocks[2] = Coordinate(0, 0);
			_blocks[3] = Coordinate(0, 1);
			break;
		case 2:
			_blocks[0] = Coordinate(1, -1);
			_blocks[1] = Coordinate(0, -1);
			_blocks[2] = Coordinate(0, 0);
			_blocks[3] = Coordinate(0, 1);
			break;
		case 3:

			_blocks[0] = Coordinate(2, 1);
			_blocks[1] = Coordinate(1, 1);
			_blocks[2] = Coordinate(0, 0);
			_blocks[3] = Coordinate(0, 1);
			break;
		}
		break;
	case Piece::SHAPE_L:
		switch (_rotation)
		{
		case 0:
			_blocks[0] = Coordinate(0, -1);
			_blocks[1] = Coordinate(0, 0);
			_blocks[2] = Coordinate(0, 1);
			_blocks[3] = Coordinate(1, 1);
			break;
		case 1:
			_blocks[0] = Coordinate(-2 ,1);
			_blocks[1] = Coordinate(-1, 1);
			_blocks[2] = Coordinate(0, 1);
			_blocks[3] = Coordinate(0, 0);
			break;
		case 2:
			_blocks[0] = Coordinate(-1, -1);
			_blocks[1] = Coordinate(0, -1);
			_blocks[2] = Coordinate(0,0);
			_blocks[3] = Coordinate(0,1);
			break;
		case 3:

			_blocks[0] = Coordinate(2, 0);
			_blocks[1] = Coordinate(1, 0);
			_blocks[2] = Coordinate(0, 1);
			_blocks[3] = Coordinate(0, 0);
			break;
		}
		break;
	case Piece::SHAPE_T:
		switch (_rotation)
		{
		case 0:
			_blocks[0] = Coordinate(0, 0);
			_blocks[1] = Coordinate(-1, 0);
			_blocks[2] = Coordinate(1, 0);
			_blocks[3] = Coordinate(0, -1);
			break;
		case 1:
			_blocks[0] = Coordinate(0, 0);
			_blocks[1] = Coordinate(0, -1);
			_blocks[2] = Coordinate(0, -2);
			_blocks[3] = Coordinate(-1, -1);
			break;
		case 2:
			_blocks[0] = Coordinate(-1, -1);
			_blocks[1] = Coordinate(0, -1);
			_blocks[2] = Coordinate(1, -1);
			_blocks[3] = Coordinate(0, 0);
			break;
		case 3:
			_blocks[0] = Coordinate(0, 0);
			_blocks[1] = Coordinate(0, -1);
			_blocks[2] = Coordinate(0, -2);
			_blocks[3] = Coordinate(1, -1);
			break;
		}
		break;
	default:
		break;
	}
}
