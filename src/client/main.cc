#include <QtWidgets/QApplication>
#include "src/client/MainWindow.h"
#include "logging.h"
//#include <iostream>
//#include <QPushButton>
//#include "src/common/Game.h"
//#include <QHostAddress>

int main(int argc, char *argv[])
{
    initialize_logger();

    _START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Started client";
    
    QApplication app(argc, argv);

	MainWindow w;
	w.setWindowTitle("Bomberman");
	w.show();

    /*Client client;
    client.show();

    return client.exec();*/

    /*QHostAddress server_address(QHostAddress::LocalHost);
    quint16 server_port = 2346;
    quint16 client_port = 500;
    std::shared_ptr<common::GameTimer> game_timer = std::make_shared<common::GameTimer>();
    net::NetworkManager manager(server_address, server_port, client_port, game_timer);
    manager.RunGame();*/

    /*MainWindow main_window;
    main_window.show();*/

    return app.exec();
}
