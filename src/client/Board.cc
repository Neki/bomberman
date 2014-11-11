#include "Board.h"
#include "Values.h"
#include <QKeyEvent>
#include <QWidget>
#include <QRectF>
#include <QSize>
#include <QDir>
#include "src/common/World.h"
#include "src/client/net/NetworkWorker.h"
#include "src/common/entity/Character.h"
#include <QPointF>
#include <QtSvg/QSvgRenderer>
#include "src/common/entity/Entity.h"
#include "src/common/net/MoveEvent.h"
#include "easylogging++.h"
#include "src/common/Direction.h"
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
	auto renderer = svg_manager_->GetSvgRenderer(path);
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
			PaintBkg(painter, x, qsizef);
			for (auto k = world_->IteratorAtBegin(a); k != world_->IteratorAtEnd(a); ++k)
			{
					PaintEntity(painter, **k, x, qsizef);
			}
		}
	}
}

