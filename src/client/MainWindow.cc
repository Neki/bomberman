#include "MainWindow.h"
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QPainter>
#include "Values.h"
#include "easylogging++.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow),
    server_handler_(std::make_shared<ServerHandler>()) {
	ui->setupUi(this);

	Board *board = new Board;
	setCentralWidget(board);

	SetScore(-5593);
	SetDeaths(199);
	SetKills(2);
}


void MainWindow::Start() {
	
}

MainWindow::~MainWindow() {
    LOG(INFO) << "deleting";
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
    //auto timer = std::make_shared<common::GameTimer>();
    //timer->StartGame();
    //net::NetworkWorker worker(1, QHostAddress("127.0.0.1"), 4567, 4568, timer);
}

void MainWindow::on_actionJoin_triggered() {
	
}

void MainWindow::on_actionQuit_triggered() {
	QApplication::quit();
}
