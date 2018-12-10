#ifndef BLOCK_H
#define BLOCK_H

#include <QList>
#include <QDebug>

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
	bool operator<(const Coordinate &c) const {
		if (y < c.y)
			return true;
		else if (y == c.y)
            return x < c.x;
		else
			return false;
	}
};

struct Block{
    Coordinate pos;
    int color;
	enum COLOR {RED, GREEN, BLUE};
	bool operator==(const Block &b) const {
		return pos == b.pos;
	}
	bool operator<(const Block&b) const {
		return pos < b.pos;
	}
};

class Piece
{
public:
	enum {CW, CCW};
	enum {LEFT, RIGHT};
	enum SHAPE {SHAPE_I, SHAPE_O, SHAPE_Z, SHAPE_S, SHAPE_J, SHAPE_L, SHAPE_T };
	enum {X_COORDINATE, Y_COORDINATE};

    Piece();
    void rotate(int direction);
	void left();
	void right();
	void down();
    bool isOverlapped(Coordinate block_pos) const; //check if this piece is overapped by a block
	bool isOverlapped(int line_pos, int coordinate_type) const; //check if this piece is overapped by a line
    QList<Block> blocks();
private:
    static const int middle_x = 5;
    Coordinate _pos;
    Coordinate _blocks[4];
    int _color;
	int _shape;
};

#endif // BLOCK_H
