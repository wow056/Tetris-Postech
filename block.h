#ifndef BLOCK_H
#define BLOCK_H

#include<QList>

struct Coordinate
{
    int x;
    int y;
};

struct Block{
    Coordinate pos;
    int color;
};

class Piece
{
public:
    Piece(int shape, int color,int type);
    void rotate();
    void move();
    bool isOverlapped(Coordinate block_pos);
    QList<Block> blocks();
private:
    Coordinate _pos;
    Coordinate _blocks[4];
    int shape;
    int color;
};

#endif // BLOCK_H
