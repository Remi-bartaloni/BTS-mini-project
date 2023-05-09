/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *haut;
    QPushButton *bat;
    QPushButton *gauch;
    QPushButton *droit;
    QPushButton *decolage;
    QPushButton *Rgoche;
    QPushButton *Rdroit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1136, 308);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        haut = new QPushButton(centralWidget);
        haut->setObjectName(QStringLiteral("haut"));
        haut->setGeometry(QRect(130, 10, 81, 51));
        bat = new QPushButton(centralWidget);
        bat->setObjectName(QStringLiteral("bat"));
        bat->setGeometry(QRect(130, 170, 81, 51));
        gauch = new QPushButton(centralWidget);
        gauch->setObjectName(QStringLiteral("gauch"));
        gauch->setGeometry(QRect(10, 90, 81, 51));
        droit = new QPushButton(centralWidget);
        droit->setObjectName(QStringLiteral("droit"));
        droit->setGeometry(QRect(250, 90, 81, 51));
        decolage = new QPushButton(centralWidget);
        decolage->setObjectName(QStringLiteral("decolage"));
        decolage->setGeometry(QRect(130, 90, 81, 51));
        Rgoche = new QPushButton(centralWidget);
        Rgoche->setObjectName(QStringLiteral("Rgoche"));
        Rgoche->setGeometry(QRect(10, 10, 101, 51));
        Rdroit = new QPushButton(centralWidget);
        Rdroit->setObjectName(QStringLiteral("Rdroit"));
        Rdroit->setGeometry(QRect(230, 10, 91, 51));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1136, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        haut->setText(QApplication::translate("MainWindow", "Haut", Q_NULLPTR));
        bat->setText(QApplication::translate("MainWindow", "Bat", Q_NULLPTR));
        gauch->setText(QApplication::translate("MainWindow", "Gauch", Q_NULLPTR));
        droit->setText(QApplication::translate("MainWindow", "Droit", Q_NULLPTR));
        decolage->setText(QApplication::translate("MainWindow", "decolage", Q_NULLPTR));
        Rgoche->setText(QApplication::translate("MainWindow", "Rotation goche", Q_NULLPTR));
        Rdroit->setText(QApplication::translate("MainWindow", "Rotation droite", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
