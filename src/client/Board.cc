#include "Board.h"
#include "Values.h"
#include <QKeyEvent>
#include <QWidget>
#include "easylogging++.h"
_INITIALIZE_EASYLOGGINGPP

Board::Board(QWidget *parent):QWidget(parent)
{
	
}

void Board::PaintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setWindow(0, 0, WIDTH_BOARD, HEIGHT_BOARD); 
	painter.setViewport(0, 0, width(), height());
	painter.setClipRect(event->rect());

	for (int i = 0; i<SQUARES_HEIGHT; i++)
	{
		for (int j = 0; j<SQUARES_WIDTH; j++)
		{
			painter.setPen(Qt::NoPen);
			QRect rect(RectSquare(j, i));
			QPixmap *pixmap;
			pixmap = new QPixmap(":/res/block.png");
			painter.drawPixmap(rect, *pixmap);
			//paintEntity(painter, entities[i,j], int i, int j);
		}
	}
}

QRect Board::RectSquare(int x, int y)
{
	return QRect(x*SIDE_SQUARE, y*SIDE_SQUARE, SIDE_SQUARE, SIDE_SQUARE);
}

bool Board::IsKeyPressEvent(QKeyEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		return true;
	}
	else
		return false;
}

bool Board::IsKeyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		return true;
	}
	else
		return false;
}

//void Board::InitGame(int nbPlayers){
//	(void) nbPlayers;
//
//	if (pixmapFire.get() == nullptr)
//	{
//		pixmapFire.reset(new QPixmap(":/res/fire.png"));
//	}
//	if (pixmapBlock.get() == nullptr)
//	{
//		pixmapBlock.reset(new QPixmap(":/res/caisse.png"));
//	}
//	if (pixmapWall.get() == nullptr)
//	{
//		pixmapWall.reset(new QPixmap(":/res/mur.png"));
//	}
//}

void Board::NewGame(int nbPlayers){
	(void)nbPlayers;
	//InitGame(nbPlayers);
}

//void Board::moveCharacter(Character *character, QKeyEvent *event){
//	QPointF Character->GetExactPosition();
//	if (IsKeyPressEvent(event)){
//		switch (event->key())
//		{
//		case Qt::Key_Left:
//			// TODO test if it is possible, then move player according to speed & change its position
//			break;
//		case Qt::Key_Up:
//			break;
//		case Qt::Key_Right:
//			break;
//		case Qt::Key_Down:
//			break;
//		default:
//			break;
//		}
//	}
//}


//// TODO Board destructor
//void Board::PaintEntity(QPainter &painter, Entity entity, int i, int j)
//{
//	// entity.getImage() -> afficher ça en (i,j)
//	painter.setPen(Qt::NoPen);
//	QRect rect(RectSquare(j, i));
//	//painter.drawPixmap(rect, image);
//}
