#ifndef SRC_CLIENT_SERVERHANDLER_H_
#define SRC_CLIENT_SERVERHANDLER_H_
#define SERVER_EXE "bombServer.exe"
#define SERVER_PORT "4567"

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QApplication>
#include <QProcess>
#include <memory>

/**
* See doc for a better understanding of QProcess: http://qt-project.org/doc/qt-5/qprocess.html
* (start process, kill it, communicating...)
*/
class ServerHandler : public QWidget {
    Q_OBJECT

public:
    ServerHandler();
    ~ServerHandler();
    void runServer();
    void terminateServer();

private slots:
    void startedServer();
    void finishedServer(int exit_code, QProcess::ExitStatus exit_status);
    void errorServer(QProcess::ProcessError error);

private:
    std::unique_ptr<QProcess> server_process_;
    bool running_ = false;
};

#endif
