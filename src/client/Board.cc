#include "Board.h"
#include "Values.h"
#include <QKeyEvent>
#include <QWidget>
#include <QRectF>
#include <QSize>
#include <QDir>
#include "src/common/World.h"
#include <QPointF>
#include <QtSvg/QSvgRenderer>
#include "src/common/entity/Entity.h"
#include "easylogging++.h"
#include <QPalette>
_INITIALIZE_EASYLOGGINGPP

Board::Board(std::shared_ptr<common::World> world, QWidget *parent) : QWidget(parent), world_(world)
{
    setGeometry(0, 50, 550, 550);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);
}

void Board::PaintEntity(QPainter &painter, common::entity::Entity &entity, QPointF x, QSizeF size)
{
	QString path = entity.GetTexturePath();
	QRectF rectF(x, size);
    QSvgRenderer *renderer = new QSvgRenderer(QCoreApplication::applicationDirPath() + "/" + path);
	renderer->render(&painter, rectF);
}

void Board::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setViewport(0, 0, width(), height());
    painter.setClipRect(event->rect());

	QSize qsize(SIDE_SQUARE, SIDE_SQUARE);
	QSizeF qsizef(qsize);

    for (int i = 0; i < world_->GetWidth(); ++i) {
		for (int j = 0; j < world_->GetHeight(); ++j) {
			QPointF x(SIDE_SQUARE * i, SIDE_SQUARE * j);
			QPoint a(i, j);
			for (auto k = world_->IteratorAtBegin(a); k != world_->IteratorAtEnd(a); ++k) {
				PaintEntity(painter, **k , x, qsizef);
			}			
		}
	}
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