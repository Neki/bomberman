#ifndef BOARD_H
#define BOARD_H

#include <QtGui>
#include <QWidget>
#include "Values.h"

class Board : public QWidget
{
	Q_OBJECT
public:
	Board(QWidget* parent = 0);
	//~Board();

private:
	QPixmap *pixmapFire;
	QPixmap *pixmapBlock;
	QPixmap *pixmapWall;

protected:
	void PaintEvent(QPaintEvent *event);
	void PaintSquare(QPainter &painter, square sq, int i, int j);
	QRect RectSquare(int x, int y);
	void InitGame(int nbPlayers);
	void NewGame(int nbPlayers);

signals:
	public slots :
};

#endif // BOARD_H