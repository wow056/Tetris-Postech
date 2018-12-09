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

struct Piece
{
    Piece(int shape, int color);
    Coordinate pos;
    Coordinate blocks[4];
    int shape;
    int color;
};

#endif // BLOCK_H
