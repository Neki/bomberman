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
#include "src/common/GameEngine.h"
#include "net/NetworkWorker.h"
#include "net/ServerEntity.h"

using net::ServerEntity;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
    void InstanciateNetworkWorker(QString address, int port);
	void Start();

public slots:
	void Timer();
	void StartNewGame();
	void SetScore(float score);
	void SetKills(int kills);
	void SetDeaths(int deaths);
    void DisplayLatency(int latency);
    void ProcessServerEntity(ServerEntity& server_entity);

private slots:
	void on_actionCreate_triggered();
	void on_actionJoin_triggered();
	void on_actionQuit_triggered();

protected:
	void keyPressEvent(QKeyEvent *evt);

private:
	Ui::MainWindow *ui;
	std::unique_ptr<Board> board_;
    std::shared_ptr<ServerHandler> server_handler_;
    std::shared_ptr<common::GameTimer> timer_;
    std::shared_ptr<common::World> world_;
    std::unique_ptr<net::NetworkWorker> network_worker_;
    std::unique_ptr<common::GameEngine> game_engine_;
};

#endif // SRC_CLIENT_MAINWINDOW_H
