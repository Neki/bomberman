#include "MainWindow.h"
#include <QTimer>
#include <QDebug>
#include <memory>
#include <QKeyEvent>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QPainter>
#include "Values.h"
#include "easylogging++.h"
#include "src/common/World.h"
#include "src/common/entity/Fire.h"
#include "src/common/entity/Block.h"
#include "src/common/entity/Bonus.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
    server_handler_(std::make_shared<ServerHandler>()),
    timer_(std::make_shared<common::GameTimer>()),
    world_(std::make_shared<common::World>(21, 21))
{
	ui->setupUi(this);
	QPoint pos(0, 0);
	world_->AddItem(std::unique_ptr<common::entity::Character>(new common::entity::Character(pos)));
	pos.setX(20);
	pos.setY(20);
	world_->AddItem(std::unique_ptr<common::entity::Bonus>(new common::entity::Bonus(pos)));

	quint32 q(21);
	pos.setX(8);
	for (int y = 3; y < 10; ++y){
		pos.setY(y);
		world_->AddItem(std::unique_ptr<common::entity::Fire>(new common::entity::Fire(pos, q)));
	}
    board_ = std::unique_ptr<Board>(new Board(world_, this));
    show();
    timer_->StartGame();

	SetScore(-5593);
	SetDeaths(199);
	SetKills(2);
}


void MainWindow::Start() {
	
}

MainWindow::~MainWindow() {
	delete ui;
}


void MainWindow::Timer() {
}


void MainWindow::keyPressEvent(QKeyEvent *evt) {
    LOG(INFO) << evt->text().toStdString();
	(void)evt;
}

void MainWindow::StartNewGame() {
	
}

void MainWindow::SetScore(float score) {
	ui->scoreLabel->setText("Score : " + QString::number(score));
}

void MainWindow::SetDeaths(int deaths) {
	ui->deathsLabel->setText("Deaths : " + QString::number(deaths));
}

void MainWindow::SetKills(int kills) {
	ui->killsLabel->setText("Kills : " + QString::number(kills));
}

void MainWindow::on_actionCreate_triggered() {
    server_handler_->runServer();
    network_worker_ = std::unique_ptr<net::NetworkWorker>(new net::NetworkWorker(1, QHostAddress("127.0.0.1"), 4567, 4568, timer_));
}

void MainWindow::on_actionJoin_triggered() {
    network_worker_ = std::unique_ptr<net::NetworkWorker>(new net::NetworkWorker(1, QHostAddress("127.0.0.1"), 4567, 4568, timer_));
}

void MainWindow::on_actionQuit_triggered() {
	QApplication::quit();
}

void MainWindow::moveCharacter(const common::entity::Character& character, QKeyEvent *event){
	QPointF posf = character.GetPositionF();
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
		quint8  id = (quint8)character.GetId();
		network_worker_->AddEvent(std::unique_ptr<common::net::MoveEvent>(new common::net::MoveEvent(pos, target, dir, id, timer_->GetTimestamp())));
	}
}

bool MainWindow::IsKeyPressEvent(QKeyEvent *event)
{
	return event->type() == QEvent::KeyPress;
}

bool MainWindow::IsKeyReleaseEvent(QKeyEvent *event)
{
	return event->type() == QEvent::KeyRelease;
}
