#ifndef SRC_CLIENT_MAINWINDOW_H
#define SRC_CLIENT_MAINWINDOW_H

#include "ui_mainwindow.h"
#include <memory>
#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QWidget>
#include "Board.h"
#include "ServerHandler.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void Start();

public slots:
	void Timer();
	void StartNewGame();
	void SetScore(float score);
	void SetKills(int kills);
	void SetDeaths(int deaths);

private slots:
	void on_actionCreate_triggered();
	void on_actionJoin_triggered();
	void on_actionQuit_triggered();

protected:
	void keyPressEvent(QKeyEvent *evt);

private:
	Ui::MainWindow *ui;
	QLabel scoreLabel;
	QLabel deathsLabel;
	QLabel killsLabel;
	std::unique_ptr<Board> board;
    std::shared_ptr<ServerHandler> server_handler_;
};

#endif // SRC_CLIENT_MAINWINDOW_H
