#ifndef SRC_CLIENT_BOARD_H
#define SRC_CLIENT_BOARD_H

#include <QtGui>
#include <QWidget>
#include <memory>
#include "Values.h"
//#include "src/common/entity/Character.h"
#include "src/common/entity/Entity.h"
#include "src/common/World.h"

class Board : public QWidget
{
	Q_OBJECT
public:
    Board(std::shared_ptr<common::World> world, QWidget* parent);

private:
	std::shared_ptr<common::World> world_;
    float side_square_;

protected:
	void PaintEntity(QPainter &painter, common::entity::Entity &entity, QPointF x, QSizeF size);
	void PaintBkg(QPainter &painter, QPointF x, QSizeF size);
	void paintEvent(QPaintEvent *event) override;
	void InitGame(int nbPlayers);
	void NewGame(int nbPlayers);
	bool IsKeyPressEvent(QKeyEvent *);
	bool IsKeyReleaseEvent(QKeyEvent *);
	//void moveCharacter(Character *character)

signals:
	public slots :
};

#endif // SRC_CLIENT_BOARD_H