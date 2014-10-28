#ifndef SRC_SERVER_PIDLOGGER_H_
#define SRC_SERVER_PIDLOGGER_H_
#include <QString>

/**
 * Logs the PID of the process in a file, and removes the file when the process is closed
 * so that one can know if the server is still running
 */
class PidLogger {
public:
      void static CreatePidFile();
      void static RemoveFile();
private:
    QString static GetFileName();
};

#endif

