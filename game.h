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
    Game(QObject *parent = nullptr);
	void setInput(int input);	//mainwindow���� KeyEvent �߻� �� ȣ�����ּ���.
	const static Coordinate board_size;
private slots:
	void update(); //time interval�� ���� �Ŀ� ����Ǵ� �Լ�
signals:
    void updateBoard(QList<Block>);
    void gameOver(int score);
    void updateNextPiece(int);
    void updatedScore(int);
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

    Piece nextPiece;
    Piece currentPiece;
    QList<Block> savedBlocks;
    QTimer *timer;
    int timer_interbal;
    int total_score;
};

#endif // GAME_H
