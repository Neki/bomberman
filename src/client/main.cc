#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "src/common/Game.h"

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
    std::cout << "Welcome to the client interface of Bomberman :)" << std::endl;

    _START_EASYLOGGINGPP(argc, argv);
    LOG(INFO) << "Started client";

    // This part should be moved to another class, that's just for test
    QApplication app(argc, argv);
    QWidget mainWindow;
    mainWindow.setFixedSize(300, 300);

    QPushButton createGameButton("Create game", &mainWindow);
    createGameButton.setCursor(Qt::PointingHandCursor);
    createGameButton.move(100, 75);

    QPushButton joinGameButton("Join game", &mainWindow);
    joinGameButton.setCursor(Qt::PointingHandCursor);
    joinGameButton.move(100, 150);

    QPushButton quitWindowButton("Quit Bomberman", &mainWindow);
    quitWindowButton.setCursor(Qt::PointingHandCursor);
    quitWindowButton.move(100, 225);

    QObject::connect(&quitWindowButton, SIGNAL(clicked()), &app, SLOT(quit()));

    mainWindow.show();

    return app.exec();
}
