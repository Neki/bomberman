#include <QtWidgets/QApplication>
#include "src/client/MainWindow.h"
#include "logging.h"
_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    initialize_logger();

    _START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Started client";
    
    QApplication app(argc, argv);

	MainWindow w;
	w.setWindowTitle("Bomberman");
	w.show();

    return app.exec();
}
