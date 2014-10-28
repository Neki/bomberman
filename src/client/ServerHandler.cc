#include "ServerHandler.h"
#include <QWidget>
#include <QFile>
#include <QtWidgets/QApplication>
#include "easylogging++.h"

ServerHandler::ServerHandler() : QWidget(), server_process_(std::unique_ptr<QProcess>(new QProcess(this))), running_(false) {
}

ServerHandler::~ServerHandler() {
    terminateServer();
}

void ServerHandler::runServer() {
    LOG(INFO) << "Starting server...";

    if (IsPidFileExisting()) {
        LOG(WARNING) << "The server.pid file exists, please check if the server is not already open";
    }
    if (running_) {
        LOG(ERROR) << "Server is already live!";
        return;
    }

    QString program = SERVER_EXE;
    QStringList arguments;
    arguments << "--port" << SERVER_PORT;

    QObject::connect(server_process_.get(), SIGNAL(started()), this, SLOT(startedServer()));
    QObject::connect(server_process_.get(), SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finishedServer(int, QProcess::ExitStatus)));
    QObject::connect(server_process_.get(), SIGNAL(error(QProcess::ProcessError)), this, SLOT(errorServer(QProcess::ProcessError)));
    
    server_process_->start(program, arguments);
}

void ServerHandler::startedServer() {
    LOG(INFO) << "Server started.";
    running_ = true;
}

void ServerHandler::terminateServer() {
    if (running_) {
        LOG(INFO) << "Terminating server...";
        server_process_->terminate();
    }
}

void ServerHandler::finishedServer(int exit_code, QProcess::ExitStatus exit_status) {
    running_ = false;
    LOG(INFO) << "Server finished (exit code: " << exit_code << ", exit status: " << exit_status << ")";
}

void ServerHandler::errorServer(QProcess::ProcessError error) {
    running_ = false;
    switch (error) {
    case QProcess::ProcessError::FailedToStart:
        LOG(ERROR) << "Server error: couldn't find '" << SERVER_EXE << "'.";
        break;
    case QProcess::ProcessError::Crashed:
        LOG(ERROR) << "Server error: server crashed.";
        break;
    default:
        LOG(ERROR) << "Server error: error code " << error << ")";
    }
}

bool ServerHandler::IsPidFileExisting() {
    std::ifstream pid_file((QCoreApplication::applicationDirPath() + "/server.pid").toStdString(), std::ios::binary);
    return pid_file ? true : false;
}
