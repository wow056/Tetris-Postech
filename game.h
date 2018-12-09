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
	void setInput(int input);	//mainwindow���� KeyEvent �߻� �� ȣ�����ּ���.
private slots:
	void update(); //time interval�� ���� �Ŀ� ����Ǵ� �Լ�
signals:
    void updateBoard(const QList<Block>);
    void gameOver();
	void sendNextBlock(Piece);
    void sendScore(int);
private:
	enum {LEFT, RIGHT};		//��� �̵�, ȸ�� ����
    bool isGameover() const;
    bool isBlockDrop() const;
    bool isBlockMove(int direction) const;
    bool isBlockRotate(int direction) const;
    bool isBlockEnd() const;
    bool isLineComplete() const;

    void deleteLine();		//�Լ� �������� updateBoard �ñ׳��� emit �ؾ���
    void setBlockDrop(); 	//�Լ� �������� updateBoard �ñ׳��� emit �ؾ���
    void setBlockMove(int direction);	//�Լ� �������� updateBoard �ñ׳��� emit �ؾ���
    void setBlockRotate(int direction);	//�Լ� �������� updateBoard �ñ׳��� emit �ؾ���
    void saveBlock();		//�Լ� �������� updateBoard �ñ׳��� emit �ؾ���
    void setNextBlock();

    Piece nextPiece;
    Piece currentPiece;
    QList<Block> savedBlocks;
    QTimer *timer;
    int timer_interbal;
};

#endif // GAME_H
