/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <easylogging++.h>
#include <QDir>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCreate;
    QAction *actionJoin;
    QAction *actionQuit;
    QAction *actionSettings;
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *killsLabel;
    QLabel *deathsLabel;
    QLabel *scoreLabel;
    QToolBar *toolBar;

	QPixmap getPixmap(QString fileName) {
		return QPixmap(QCoreApplication::applicationDirPath() + QDir::separator() + QString("res") + QDir::separator() + QString(fileName));
	}

    void setupUi(QMainWindow *MainWindow) {
        if (MainWindow->objectName().isEmpty()) {
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        }

        // Actions
        actionCreate = new QAction(MainWindow);
        actionCreate->setObjectName(QStringLiteral("actionCreate"));
        actionCreate->setCheckable(false);
        QIcon icon;
		icon.addPixmap(getPixmap("create.png"));
        actionCreate->setIcon(icon);

        actionJoin = new QAction(MainWindow);
        actionJoin->setObjectName(QStringLiteral("actionJoin"));
        QIcon icon1;
		icon1.addPixmap(getPixmap("join.png"));
		actionJoin->setIcon(icon1);

        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QIcon icon2;
		icon2.addPixmap(getPixmap("quit.png"));
		actionQuit->setIcon(icon2);

        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon3;
		icon3.addPixmap(getPixmap("settings.png"));
		actionSettings->setIcon(icon3);

        // Vertical layout definition
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setMinimumSize(QSize(800, 549));
        centralwidget->move(0, 51);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(600, 10, 98, 59));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        // Labels
        killsLabel = new QLabel(widget);
        killsLabel->setObjectName(QStringLiteral("killsLabel"));
        killsLabel->setMinimumSize(QSize(79, 16));
        verticalLayout->addWidget(killsLabel);

        deathsLabel = new QLabel(widget);
        deathsLabel->setObjectName(QStringLiteral("deathsLabel"));
        deathsLabel->setMinimumSize(QSize(96, 13));
        verticalLayout->addWidget(deathsLabel);

        scoreLabel = new QLabel(widget);
        scoreLabel->setObjectName(QStringLiteral("scoreLabel"));
        scoreLabel->setMinimumSize(QSize(37, 16));
        verticalLayout->addWidget(scoreLabel);

        // Toolbar
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
		toolBar->setMovable(false);
        toolBar->addAction(actionCreate);
        toolBar->addSeparator();
        toolBar->addAction(actionJoin);
        toolBar->addSeparator();
        toolBar->addAction(actionSettings);
        toolBar->addSeparator();
        toolBar->addAction(actionQuit);

        retranslateUi(MainWindow);

        MainWindow->setFixedSize(800, 600);

        QMetaObject::connectSlotsByName(MainWindow);
    }

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionCreate->setText(QApplication::translate("MainWindow", "Create", 0));
#ifndef QT_NO_TOOLTIP
        actionCreate->setToolTip(QApplication::translate("MainWindow", "create game", 0));
#endif // QT_NO_TOOLTIP
        actionJoin->setText(QApplication::translate("MainWindow", "Join", 0));
#ifndef QT_NO_TOOLTIP
        actionJoin->setToolTip(QApplication::translate("MainWindow", "join an existing game", 0));
#endif // QT_NO_TOOLTIP
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
#ifndef QT_NO_TOOLTIP
        actionQuit->setToolTip(QApplication::translate("MainWindow", "close game", 0));
#endif // QT_NO_TOOLTIP
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0));
#ifndef QT_NO_TOOLTIP
        actionSettings->setToolTip(QApplication::translate("MainWindow", "settings of the player", 0));
#endif // QT_NO_TOOLTIP
        killsLabel->setText(QApplication::translate("MainWindow", "Number of kills : ", 0));
        deathsLabel->setText(QApplication::translate("MainWindow", "Number of deaths : ", 0));
        scoreLabel->setText(QApplication::translate("MainWindow", "Score : ", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
