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
	Board(common::World* world, QWidget* parent = 0);
	//~Board();

private:
	common::World *world_;
	/*std::unique_ptr<QPixmap> pixmapFire;
	std::unique_ptr<QPixmap> pixmapBlock;
	std::unique_ptr<QPixmap> pixmapWall;*/

protected:
	void PaintEntity(QPainter &painter, common::entity::Entity &entity, QPointF x, QSizeF size);
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