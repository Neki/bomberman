#include "Board.h"
#include "Values.h"
#include <QKeyEvent>
#include <QWidget>
#include <QRectF>
#include <QSize>
#include <QDir>
#include "src/common/World.h"
#include "src/common/entity/Character.h"
#include <QPointF>
#include <QtSvg/QSvgRenderer>
#include "src/common/entity/Entity.h"
#include "easylogging++.h"
#include <QPalette>
_INITIALIZE_EASYLOGGINGPP

Board::Board(std::shared_ptr<common::World> world, QWidget *parent) :
    QWidget(parent),
    world_(world),
    svg_manager_(new SvgManager()),
    side_square_(500 / world->GetWidth())
{
    setGeometry(0, 50, 500, 550);
}

void Board::PaintEntity(QPainter &painter, common::entity::Entity &entity, QPointF x, QSizeF size)
{
	QString path = entity.GetTexturePath();
	QRectF rectF(x, size);
    auto renderer = svg_manager_->GetSvgRenderer(path);
	renderer->render(&painter, rectF);
}

void Board::PaintBkg(QPainter &painter, QPointF x, QSizeF size){
	QString path = "res/bkg.svg";
	QRectF rectF(x, size);
	QSvgRenderer *renderer = new QSvgRenderer(QCoreApplication::applicationDirPath() + "/" + path);
	renderer->render(&painter, rectF);
}

void Board::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setViewport(0, 0, width(), height());
    painter.setClipRect(event->rect());

    QSize qsize(side_square_, side_square_);
  QSizeF qsizef(qsize);

    for (int i = 0; i < world_->GetWidth(); ++i) {
    for (int j = 0; j < world_->GetHeight(); ++j) {
            QPointF x(side_square_ * i, side_square_ * j);
			QPoint a(i, j);
			if (world_->IsEntitiesEmpty(a) ){
				PaintBkg(painter, x, qsizef);
			}
			else {
				for (auto k = world_->IteratorAtBegin(a); k != world_->IteratorAtEnd(a); ++k)
				{
					PaintEntity(painter, **k, x, qsizef);
				}
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

void Board::moveCharacter(common::entity::Character *character, QKeyEvent *event){
	QPointF pos = character->GetPositionF();
	int x = pos.x();
	int y = pos.y();

	if (IsKeyPressEvent(event)){
		switch (event->key())
		{
		case Qt::Key_Left:
			--x;
			break;
		case Qt::Key_Up:
			++y;
			break;
		case Qt::Key_Right:
			++x;
			break;
		case Qt::Key_Down:
			--y;
			break;
		default:
			break;
		}
	}
	// TODO character -> SetPositionF(x,y) ??
}
