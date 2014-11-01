#include "ServerHandler.h"
#include <QWidget>
#include <QFile>
#include <QtWidgets/QApplication>
#include "easylogging++.h"
#ifdef _WIN32
    #include <tlhelp32.h>
#else
    #include <sys/types.h>  
    #include <signal.h>
#endif

ServerHandler::ServerHandler() : QWidget(), server_process_(std::unique_ptr<QProcess>(new QProcess(this))), running_(false) {
}

ServerHandler::~ServerHandler() {
    terminateServer();
}

void ServerHandler::runServer() {
    LOG(INFO) << "Starting server...";

    if (IsAlreadyRunning()) {
        LOG(WARNING) << "The server is already running (cf server.pid file).";
        return;
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
        server_process_->kill();
        server_process_->waitForFinished(1000);
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
        break;
    default:
        LOG(ERROR) << "Server error: error code " << error << ")";
    }
}

bool ServerHandler::IsAlreadyRunning() {
    std::ifstream pid_file((QCoreApplication::applicationDirPath() + "/server.pid").toStdString());
    if (pid_file.is_open()) {
        std::string line;
        getline(pid_file, line);
        std::istringstream iss(line);
        int pid_number;
        iss >> pid_number;

        LOG(INFO) << "pid:" << pid_number;

        #ifdef _WIN32
            HANDLE pss = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

            PROCESSENTRY32 pe = { 0 };  
            pe.dwSize = sizeof(pe);  

            if (Process32First(pss, &pe)) {
                do {
                    if (pe.th32ProcessID == pid_number) {
                        return true;
                    }
                } while (Process32Next(pss, &pe));
            }

            CloseHandle(pss);

            return false;
        #else
            return 0 == kill(pid_number, 0); 
        #endif
    }

    return false;
}
