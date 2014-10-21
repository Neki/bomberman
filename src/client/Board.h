#ifndef GUI_BOARD_H
#define GUI_BOARD_H

#include <QtGui>
#include <QWidget>
#include <memory>
#include "Values.h"
//#include "Character.h"

class Board : public QWidget
{
	Q_OBJECT
public:
	Board(QWidget* parent = 0);
	//~Board();

private:
	/*std::unique_ptr<QPixmap> pixmapFire;
	std::unique_ptr<QPixmap> pixmapBlock;
	std::unique_ptr<QPixmap> pixmapWall;*/

protected:
	void PaintEvent(QPaintEvent *event);
	//void PaintEntity(QPainter &painter, Entity entity, int i, int j);
	QRect RectSquare(int x, int y);
	//void InitGame(int nbPlayers);
	void NewGame(int nbPlayers);
	bool IsKeyPressEvent(QKeyEvent *);
	bool IsKeyReleaseEvent(QKeyEvent *);
	//void moveCharacter(Character *character)

signals:
	public slots :
};

#endif // GUI_BOARD_H