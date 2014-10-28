#include "PidLogger.h"
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include "easylogging++.h"

void PidLogger::CreatePidFile() {
    QFile file(GetFileName());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        LOG(ERROR) << "Could not open file to write pid.";
        exit(0);
    }

    QTextStream out(&file);
    out << QCoreApplication::applicationPid();
    file.close();
}

void PidLogger::RemoveFile() {
    remove(GetFileName().toStdString().c_str());
}

QString PidLogger::GetFileName() {
    return QCoreApplication::applicationDirPath() + "/server.pid";
}
