#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cliant.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_haut_clicked();

    void on_decolage_clicked();

private:
    Ui::MainWindow *ui;

    cliant *envoi;

};

#endif // MAINWINDOW_H
