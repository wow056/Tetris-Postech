#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QList>
#include "block.h"

class Game
{
    Q_OBJECT
public:
    Game();
    void routine();
signals:
    void updateBoard(QList<Block>);
    void sendScore(int);
private:
    bool isGameover() const;
    bool isBlockDrop() const;
    bool isBlockMove() const;
    bool isBlockRotate() const;
    bool isBlockEnd() const;
    bool isLineComplete() const;

    void deleteLine();
    void setBlockDrop();
    void setBlockMove();
    void setBlockRotate();
    void saveBlock();
    void setNextBlock();

    Piece nextPiece;
    Piece currentPiece;
    QList<Block> savedBlocks;

};

#endif // GAME_H
