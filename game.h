#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QList>
#include "block.h"
#include <QObject>
#include <QTimer>


class Game: public QObject
{
    Q_OBJECT
public:
    Game(QObject *parent = nullptr);
	void setInput(int input);	//mainwindow에서 KeyEvent 발생 시 호출해주세요.
private slots:
	void update(); //time interval이 지난 후에 실행되는 함수
signals:
    void updateBoard(const QList<Block>);
    void gameOver();
	void sendNextBlock(Piece);
    void sendScore(int);
private:
	enum {LEFT, RIGHT};		//블록 이동, 회전 방향
    bool isGameover() const;
    bool isBlockDrop() const;
    bool isBlockMove(int direction) const;
    bool isBlockRotate(int direction) const;
    bool isBlockEnd() const;
    bool isLineComplete() const;

    void deleteLine();		//함수 마지막에 updateBoard 시그널을 emit 해야함
    void setBlockDrop(); 	//함수 마지막에 updateBoard 시그널을 emit 해야함
    void setBlockMove(int direction);	//함수 마지막에 updateBoard 시그널을 emit 해야함
    void setBlockRotate(int direction);	//함수 마지막에 updateBoard 시그널을 emit 해야함
    void saveBlock();		//함수 마지막에 updateBoard 시그널을 emit 해야함
    void setNextBlock();

    Piece nextPiece;
    Piece currentPiece;
    QList<Block> savedBlocks;
    QTimer *timer;
    int timer_interbal;
};

#endif // GAME_H
