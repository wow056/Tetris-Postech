#ifndef BLOCK_H
#define BLOCK_H

#include <QList>
#include <QDebug>
#include <>

struct Coordinate
{
    int x;
    int y;

	Coordinate()
		:x(-1), y(-1) {}
	Coordinate(int x, int y)
		:x(x), y(y) {}
	Coordinate operator+(const Coordinate &c) const{
		Coordinate result;
		result.x = x + c.x;
		result.y = y + c.y;
		return result;
	}
	bool operator==(const Coordinate &c) const {
		return (x == c.x) && (y == c.y);
	}
};

struct Block{
    Coordinate pos;
    int color;
	enum COLOR {RED, GREEN, BLUE};
};

class Piece
{
public:
	enum {CW, CCW};
	enum SHAPE {SHAPE_I, SHAPE_O, SHAPE_Z, SHAPE_S, SHAPE_J, SHAPE_L, SHAPE_T };

    Piece();
    void rotate(int direction);
	void left();
	void right();
	void down();
    bool isOverlapped(Coordinate block_pos);
    QList<Block> blocks();
private:
	static const int middle_x = 10;
    Coordinate _pos;
    Coordinate _blocks[4];
    int _color;
	int _shape;
};

#endif // BLOCK_H
