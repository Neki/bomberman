#include <iostream>
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    std::cout << "Welcome to the client interface of Bomberman :)" << std::endl;

    // This part should be moved to another class, that's just for test
    QApplication app(argc, argv);
    QWidget mainWindow;
    mainWindow.setFixedSize(300, 300);

    QPushButton button("Create game", &mainWindow);
    button.setCursor(Qt::PointingHandCursor);
    button.move(100, 100);

    QPushButton button2("Join game", &mainWindow);
    button2.setCursor(Qt::PointingHandCursor);
    button2.move(100, 200);

    mainWindow.show();

    return app.exec();
}
