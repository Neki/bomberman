#include "Board.h"
#include "Values.h"
#include <QWidget>
#include <iostream>

Board::Board(QWidget *parent):QWidget(parent)
{
	
}

void Board::PaintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.setWindow(0, 0, WIDTH_BOARD, HEIGHT_BOARD); 
	painter.setViewport(0, 0, width(), height());
	painter.setClipRect(event->rect());
}

QRect Board::RectSquare(int x, int y)
{
	return QRect(x*SIDE_SQUARE, y*SIDE_SQUARE, SIDE_SQUARE, SIDE_SQUARE);
}

void Board::InitGame(int nbPlayers){
	if (pixmapFire.get() == nullptr)
	{
		pixmapFire.reset(new QPixmap(":/res/fire.png"));
	}
	if (pixmapBlock.get() == nullptr)
	{
		pixmapBlock.reset(new QPixmap(":/res/caisse.png"));
	}
	if (pixmapWall.get() == nullptr)
	{
		pixmapWall.reset(new QPixmap(":/res/mur.png"));
	}
}

void Board::NewGame(int nbPlayers){
	InitGame(nbPlayers);
}

// TODO Board destructor

void Board::PaintSquare(QPainter &painter, square sq, int i, int j)
{
	painter.setPen(Qt::NoPen);
	QRect rect(RectSquare(j, i));
	switch (sq)
	{
	case VIDE:
		return;
		break;
	case FIRE:
		painter.drawPixmap(rect, *pixmapFire);
		return;
		break;
	case MUR:
		painter.drawPixmap(rect, *pixmapWall);
		break;
	case MUR_DESTRUCTIBLE:
		painter.drawPixmap(rect, *pixmapBlock);
		break;
	// TODO Add bonus
	default:
		std::wcerr << "" << endl;
		break;
	}
}
