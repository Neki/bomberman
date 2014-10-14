#include "Board.h"
#include "Values.h"
#include <QWidget>


Board::Board(QWidget *parent):QWidget(parent)
{
	
}

void Board::PaintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	painter.setWindow(0, 0, LARGEUR_TERRAIN, HAUTEUR_TERRAIN); 
	painter.setViewport(0, 0, width(), height());
	painter.setClipRect(event->rect());
}

QRect Board::RectSquare(int x, int y)
{
	return QRect(x*COTE_CASE, y*COTE_CASE, COTE_CASE, COTE_CASE);
}

void Board::InitGame(int nbPlayers){
	if (pixmap_fire == NULL)
	{
		pixmap_fire = new QPixmap(":/res/fire.png");
	}
	if (pixmap_block == NULL)
	{
		pixmap_block = new QPixmap(":/res/caisse.png");
	}
	if (pixmap_wall == NULL)
	{
		pixmap_wall = new QPixmap(":/res/mur.png");
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
	case RAPIDE:
		painter.setPen(Qt::green);
		painter.setBrush(Qt::green);
		painter.drawText(rect, Qt::AlignCenter, "R");
		break;
	case PUISSANCE:
		painter.setPen(Qt::green);
		painter.setBrush(Qt::green);
		painter.drawText(rect, Qt::AlignCenter, "P");
		break;
	case BOMBE_SUPPLEMENTAIRE:
		painter.setPen(Qt::green);
		painter.setBrush(Qt::green);
		painter.drawText(rect, Qt::AlignCenter, "B");
		break;
	case DETONATEUR:
		painter.setPen(Qt::green);
		painter.setBrush(Qt::green);
		painter.drawText(rect, Qt::AlignCenter, "D");
		break;
	default:
		break;
	}
}
