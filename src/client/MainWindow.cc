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
    world_(std::make_shared<common::World>(21, 21)),
	network_worker_(std::make_shared<net::NetworkWorker>(client_id_, host_adress_, server_port_, local_port_, timer_))
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
    board_ = std::unique_ptr<Board>(new Board(world_, network_worker_,this));
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

//int nbColumns = 15; // = background.width / block.size
//int nbRows = 15; // = background.height / block.size

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
