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
#include "src/common/GameTimer.h"
#include "net/NetworkWorker.h"

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
	bool IsKeyPressEvent(QKeyEvent *);
	bool IsKeyReleaseEvent(QKeyEvent *);

private:
	Ui::MainWindow *ui;
	QLabel scoreLabel;
	QLabel deathsLabel;
	QLabel killsLabel;
	std::unique_ptr<Board> board_;
    std::shared_ptr<ServerHandler> server_handler_;
    std::shared_ptr<common::GameTimer> timer_;
    std::shared_ptr<common::World> world_;
    std::unique_ptr<net::NetworkWorker> network_worker_;
	void moveCharacter(common::entity::Character *character, QKeyEvent *event);
};

#endif // SRC_CLIENT_MAINWINDOW_H
