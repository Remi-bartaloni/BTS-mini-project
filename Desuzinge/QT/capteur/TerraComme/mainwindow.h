#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

#include "mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //void clien(std::string rq2);
    //void clien2();
     MyThread *thread;
     vector<Mesures> conteneur;



private slots:
    void Test_Led();
    void Test_Ventilateur();
    void acquisition();
    void manuelle();
    void test_thread();
    void pourVoir();
    void automatique(Mesures);
    void affich_historique();
};

#endif // MAINWINDOW_H
