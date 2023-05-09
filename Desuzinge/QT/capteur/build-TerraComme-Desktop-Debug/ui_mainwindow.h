/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *Quitter;
    QGroupBox *Test;
    QPushButton *Led;
    QPushButton *Ventilateur;
    QLabel *Temp;
    QLabel *Humidity;
    QGroupBox *groupBox;
    QPushButton *Aquisition;
    QRadioButton *Manuler;
    QRadioButton *Automatique;
    QPlainTextEdit *plainTextEdit;
    QLabel *Temp_2;
    QLabel *Humidity_2;
    QPushButton *historique;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 556);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Quitter = new QPushButton(centralWidget);
        Quitter->setObjectName(QStringLiteral("Quitter"));
        Quitter->setGeometry(QRect(10, 450, 130, 40));
        Test = new QGroupBox(centralWidget);
        Test->setObjectName(QStringLiteral("Test"));
        Test->setGeometry(QRect(10, 300, 141, 141));
        QFont font;
        font.setPointSize(15);
        Test->setFont(font);
        Led = new QPushButton(Test);
        Led->setObjectName(QStringLiteral("Led"));
        Led->setGeometry(QRect(0, 30, 130, 40));
        Ventilateur = new QPushButton(Test);
        Ventilateur->setObjectName(QStringLiteral("Ventilateur"));
        Ventilateur->setGeometry(QRect(0, 90, 130, 40));
        Temp = new QLabel(centralWidget);
        Temp->setObjectName(QStringLiteral("Temp"));
        Temp->setGeometry(QRect(580, 20, 131, 71));
        QFont font1;
        font1.setPointSize(40);
        Temp->setFont(font1);
        Temp->setLayoutDirection(Qt::RightToLeft);
        Humidity = new QLabel(centralWidget);
        Humidity->setObjectName(QStringLiteral("Humidity"));
        Humidity->setGeometry(QRect(230, 20, 131, 71));
        Humidity->setFont(font1);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 161, 191));
        groupBox->setFont(font);
        Aquisition = new QPushButton(groupBox);
        Aquisition->setObjectName(QStringLiteral("Aquisition"));
        Aquisition->setGeometry(QRect(10, 140, 130, 40));
        Manuler = new QRadioButton(groupBox);
        Manuler->setObjectName(QStringLiteral("Manuler"));
        Manuler->setEnabled(true);
        Manuler->setGeometry(QRect(20, 100, 104, 22));
        QFont font2;
        font2.setPointSize(10);
        Manuler->setFont(font2);
        Manuler->setChecked(true);
        Automatique = new QRadioButton(groupBox);
        Automatique->setObjectName(QStringLiteral("Automatique"));
        Automatique->setGeometry(QRect(20, 50, 121, 22));
        Automatique->setFont(font2);
        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(190, 110, 591, 341));
        Temp_2 = new QLabel(centralWidget);
        Temp_2->setObjectName(QStringLiteral("Temp_2"));
        Temp_2->setGeometry(QRect(710, 20, 61, 71));
        Temp_2->setFont(font1);
        Humidity_2 = new QLabel(centralWidget);
        Humidity_2->setObjectName(QStringLiteral("Humidity_2"));
        Humidity_2->setGeometry(QRect(360, 20, 121, 71));
        Humidity_2->setFont(font1);
        historique = new QPushButton(centralWidget);
        historique->setObjectName(QStringLiteral("historique"));
        historique->setGeometry(QRect(190, 460, 591, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 27));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        Quitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        Test->setTitle(QApplication::translate("MainWindow", "Test", 0));
        Led->setText(QApplication::translate("MainWindow", "Led", 0));
        Ventilateur->setText(QApplication::translate("MainWindow", "Ventilateur", 0));
        Temp->setText(QApplication::translate("MainWindow", "00.00", 0));
        Humidity->setText(QApplication::translate("MainWindow", "00.00", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Mode", 0));
        Aquisition->setText(QApplication::translate("MainWindow", "Aquisition", 0));
        Manuler->setText(QApplication::translate("MainWindow", "Manuler", 0));
        Automatique->setText(QApplication::translate("MainWindow", "Automatique", 0));
        Temp_2->setText(QApplication::translate("MainWindow", "\302\260C", 0));
        Humidity_2->setText(QApplication::translate("MainWindow", "%RH", 0));
        historique->setText(QApplication::translate("MainWindow", "Historique", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
