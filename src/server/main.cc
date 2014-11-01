#define NOMINMAX // Required for Windows to avoid QTime errors
#include <iostream>
#include "logging.h"
#include <memory.h>
#include "src/common/GameTimer.h"
#include "net/GameNetworkWorker.h"
#include "src/server/net/Client.h"
#include "PidLogger.h"
#include <QtWidgets/QApplication>
#include <QCommandLineParser>

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
    initialize_logger();
    _START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Starting bomberman server...";

    QApplication app(argc, argv);

    QCommandLineParser parser;
    QCommandLineOption portOption("port", "Server port", "port", "4567");
    parser.addOption(portOption);
    QCommandLineOption verboseOption("v", "Verbose level");
    parser.addOption(verboseOption);
    parser.process(app);

    int port = parser.value(portOption).toInt();
    if (port == 0) {
        LOG(ERROR) << "You must specify a server port with the --port parameter";
        exit(0);
    }
    
    PidLogger::CreatePidFile();

    net::Client client(1, QHostAddress("127.0.0.1"), 4568);
    std::vector<net::Client> clients;
    clients.push_back(client);
    auto timer = std::make_shared<common::GameTimer>();
    timer->StartGame();
    LOG(DEBUG) << "Listening on port " << port;
    net::GameNetworkWorker worker(port, timer, clients);

    return app.exec();
}
