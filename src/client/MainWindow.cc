#include "MainWindow.h"
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QPainter>
#include "Values.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui-> setupUi(this);

	Board *board = new Board;
	setCentralWidget(board);

	SetScore(-5593);
	SetDeaths(199);
	SetKills(2);
}


void MainWindow::Start()
{
	
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::Timer()
{
}


void MainWindow::keyPressEvent(QKeyEvent *evt)
{
	(void)evt;
}

void MainWindow::StartNewGame(){
	
}

//int nbColumns = 15; // = background.width / block.size
//int nbRows = 15; // = background.height / block.size

void MainWindow::SetScore(float score){
	ui->scoreLabel->setText("Score : " + QString::number(score));
}

void MainWindow::SetDeaths(int deaths){
	ui->deathsLabel->setText("Deaths : " + QString::number(deaths));
}

void MainWindow::SetKills(int kills){
	ui->killsLabel->setText("Kills : " + QString::number(kills));
}

void MainWindow::on_actionCreate_clicked()
{

}

void MainWindow::on_actionJoin_clicked()
{
	
}

void MainWindow::on_actionQuit_triggered()
{
	QApplication::quit();
}
