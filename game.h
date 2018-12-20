#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include "block.h"

const int GAME_WIDTH = 10;
const int GAME_HEIGHT = 20;

class Game: public QObject
{
    Q_OBJECT
public:
	enum MODE
	{
		Normal, Item, Speed
	};
    Game(int mode, QObject *parent = nullptr);
	void setInput(int input);
	const static Coordinate board_size;
private slots:
	void update();
	void updateSpeed();
signals:
    void updateBoard(QList<Block>);
    void gameOver(int score);
    void updateNextPiece(int);
    void updatedScore(int);
	void updatedSpeed(float);
private:
    bool isGameover() const;
    bool isBlockDroppable() const;
    bool isBlockMove(int direction) const;
    bool isBlockRotate(int direction) const;
    int findCompleteLine() const;

    void deleteLine(int line_index);	//�Լ� �������� putOutput �Լ� ȣ��
    void setBlockDrop(); 				//�Լ� �������� putOutput �Լ� ȣ��
    void setBlockMove(int direction);	//�Լ� �������� putOutput �Լ� ȣ��
    void setBlockRotate(int direction);	//�Լ� �������� putOutput �Լ� ȣ��

    void saveBlock();

    void setNextPiece();				//�Լ� �������� sendNextBlock �ñ׳� ȣ��
	void putOutput();					//�Լ� �������� updateBoard �ñ׳� ȣ��
	void increaseScore(int n);

	const static float SpeedIncrement;

    Piece nextPiece;
    Piece currentPiece;
    QList<Block> savedBlocks;
    QTimer *timer;
	QTimer *timer_speedmode;
    int timer_interbal;
    int total_score;
	int mode;
};

#endif // GAME_H
