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
private:
    Coordinate pos;
    Coordinate blocks[4];
    int shape;
    int color;
};

#endif // BLOCK_H
