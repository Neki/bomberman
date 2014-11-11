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

Board::Board(std::shared_ptr<common::World> world, std::shared_ptr<net::NetworkWorker> network_worker, QWidget *parent) :
    QWidget(parent),
    world_(world),
	network_worker_(network_worker),
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
	if (event->type() == QEvent::KeyRelease)
	{
		return true;
	}
	else
		return false;
}

void Board::moveCharacter(common::entity::Character *character, QKeyEvent *event){
	QPointF posf = character->GetPositionF();
	QPoint pos(posf.x(), posf.y());
	int x = pos.x();
	int y = pos.y();
	common::Direction dir;
	if (IsKeyPressEvent(event)){
		switch (event->key())
		{
		case Qt::Key_Left:
			--x;
			dir = common::Direction::LEFT;
			break;
		case Qt::Key_Up:
			++y;
			dir = common::Direction::UP;
			break;
		case Qt::Key_Right:
			++x;
			dir = common::Direction::RIGHT;
			break;
		case Qt::Key_Down:
			--y;
			dir = common::Direction::DOWN;
			break;
		default:
			break;
		}
	}
	QPoint target(x, y);
	if (world_->IsWalkable(target)){
		quint32 timestamp = QDateTime::currentDateTime().toTime_t();
		quint8  id = (quint8)character->GetId();
		network_worker_->AddEvent(std::unique_ptr<common::net::MoveEvent>(new common::net::MoveEvent(pos, target, dir, id, timestamp)));
	}
}
