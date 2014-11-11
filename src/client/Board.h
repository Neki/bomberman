#ifndef SRC_CLIENT_BOARD_H
#define SRC_CLIENT_BOARD_H

#include <QtGui>
#include <QWidget>
#include <memory>
#include "Values.h"
//#include "src/common/entity/Character.h"
#include "src/common/entity/Entity.h"
#include "src/common/World.h"
#include "src/client/net/NetworkWorker.h"
#include "SvgManager.h"

class Board : public QWidget
{
	Q_OBJECT
public:
	Board(std::shared_ptr<common::World> world, std::shared_ptr<net::NetworkWorker> network_worker, QWidget* parent);

private:
	std::shared_ptr<common::World> world_;
    std::unique_ptr<SvgManager> svg_manager_;
	std::shared_ptr<net::NetworkWorker> network_worker_;
    float side_square_;

protected:
	void PaintEntity(QPainter &painter, common::entity::Entity &entity, QPointF x, QSizeF size);
	void PaintBkg(QPainter &painter, QPointF x, QSizeF size);
	void paintEvent(QPaintEvent *event) override;
	bool IsKeyPressEvent(QKeyEvent *);
	bool IsKeyReleaseEvent(QKeyEvent *);
	void moveCharacter(common::entity::Character *character, QKeyEvent *event);

signals:
	public slots :
};

#endif // SRC_CLIENT_BOARD_H