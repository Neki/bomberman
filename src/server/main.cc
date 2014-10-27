#define NOMINMAX
#include <iostream>
#include "logging.h"
#include "src/common/GameTimer.h"
#include "net/Client.h"
#include "net/GameNetworkWorker.h"
#include <memory.h>
#include <QtWidgets/QApplication>
#include "src/server/net/Client.h"
_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
    initialize_logger();
    _START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Starting bomberman server...";
    int port;

    if (argc < 3) {
        LOG(ERROR) << "Not enough parameters. You should mention a -port parameter.";
        exit(0);
    }
    else {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-port") == 0) {
                port = atoi(argv[++i]);
            }
            else {
                LOG(ERROR) << "You should mention a -port parameter.";
                exit(0);
            }
        }
    }

    QApplication app(argc, argv);
    
    net::Client client(1, QHostAddress("127.0.0.1"), port+1);
    std::vector<net::Client> clients;
    clients.push_back(client);
    auto timer = std::make_shared<common::GameTimer>();
    timer->StartGame();
    LOG(DEBUG) << "Listening on port " << port;
    net::GameNetworkWorker worker(port, timer, clients);

    return app.exec();
}
