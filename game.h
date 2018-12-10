#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include "block.h"

class Game: public QObject
{
    Q_OBJECT
public:
    Game(QObject *parent = nullptr);
	void setInput(int input);	//mainwindow에서 KeyEvent 발생 시 호출해주세요.
private slots:
	void update(); //time interval이 지난 후에 실행되는 함수
signals:
    void updateBoard(const QList<Block>&);
    void gameOver();
	void sendNextBlock(Piece);
    void sendScore(int);
private:
    bool isGameover() const;
    bool isBlockDrop() const;
    bool isBlockMove(int direction) const;
    bool isBlockRotate(int direction) const;
    bool isBlockEnd() const;
    bool isLineComplete() const;

    void deleteLine();					//함수 마지막에 putOutput 함수 호출
    void setBlockDrop(); 				//함수 마지막에 putOutput 함수 호출
    void setBlockMove(int direction);	//함수 마지막에 putOutput 함수 호출
    void setBlockRotate(int direction);	//함수 마지막에 putOutput 함수 호출

    void saveBlock();

    void setNextPiece();				//함수 마지막에 sendNextBlock 시그널 호출
	void putOutput();					//함수 마지막에 updateBoard 시그널 호출

    Piece nextPiece;
    Piece currentPiece;
    QList<Block> savedBlocks;
    QTimer *timer;
    int timer_interbal;
};

#endif // GAME_H
