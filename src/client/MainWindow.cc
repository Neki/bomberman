#include "MainWindow.h"
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <memory>
#include <QKeyEvent>
#include <QtWidgets/QMainWindow>
#include <QWidget>
#include <QPainter>
#include "Values.h"
#include "easylogging++.h"
#include "src/common/World.h"
#include "src/common/entity/Entity.h"
#include "ServerDialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),
  server_handler_(std::make_shared<ServerHandler>()),
  timer_(std::make_shared<common::GameTimer>()),
  game_engine_(new common::GameEngine())
{
  ui->setupUi(this);

  world_ = std::shared_ptr<common::World>(game_engine_->GetWorld());
  board_ = std::unique_ptr<Board>(new Board(world_, this));
  show();
  timer_->StartGame();

  SetScore(0);
  SetDeaths(0);
  SetKills(0);
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

  if (evt->key() == Qt::Key_Down) {
    // émettre un MoveEvent
  }
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

  std::istringstream iss(SERVER_PORT);
  int port;
  iss >> port;

  InstanciateNetworkWorker("127.0.0.1", port);
  ui->actionCreate->setEnabled(false);
  ui->actionJoin->setEnabled(false);
}

void MainWindow::on_actionJoin_triggered() {
  ServerDialog server_dialog;
  server_dialog.setModal(true);
  if (server_dialog.exec()) {
    QString address = server_dialog.GetServerAddress();
    int port = server_dialog.GetServerPort();

    LOG(INFO) << "Trying to connect on " << address.toStdString() << ":" << port << "...";
    InstanciateNetworkWorker("127.0.0.1", port);

    ui->actionCreate->setEnabled(false);
    ui->actionJoin->setEnabled(false);
  }
}

void MainWindow::on_actionQuit_triggered() {
  QApplication::quit();
}

void MainWindow::InstanciateNetworkWorker(QString address, int port) {
  network_worker_ = std::unique_ptr<net::NetworkWorker>(new net::NetworkWorker(1, QHostAddress(address), port, port + 1, timer_));
  // Ici il faudrait pouvoir connecter network_worker à un signal ServerNotRespondingPing() du worker
  // qui se déclencherait si le serveur ne répond pas au ping, ça permet de savoir que ce serveur n'est pas (ou plus) bon
  // et de revenir en mode non-connecté

  QObject::connect(network_worker_.get(), SIGNAL(Latency(int)), this, SLOT(DisplayLatency(int)));
  QObject::connect(network_worker_.get(), SIGNAL(EntityReceived(ServerEntity&)), this, SLOT(ProcessServerEntity(ServerEntity&)));
}

void MainWindow::DisplayLatency(int latency) {
  ui->latencyLabel->setText("Latence : " + QString::number(latency / 1000) + "s");
}

void MainWindow::ProcessServerEntity(ServerEntity& server_entity) {
  // Ici il faut pouvoir updater une Entity à la place de l'ajouter
  // L'ajout de l'entité ne fonctionne d'ailleurs pas (je n'ai pas encore investigué)
  game_engine_->AddEntity(std::unique_ptr<common::entity::Entity>(server_entity.GetEntity()));
}
