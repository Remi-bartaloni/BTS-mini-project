using namespace std;

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serveur.h"
#include "cliant.h"



using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_haut_clicked()
{

}

void MainWindow::on_decolage_clicked()
{
    static int flag = 0;
    char decoler[] = "AT*REF=1,290718208";
    char aterire[] = "AT*REF=2,290717696";

    if (flag == 0)
    {
        flag = 1;
        envoi = new cliant;
        envoi->envoier(decoler);
    }
    else
    {
        flag = 0;

        envoi->envoier(aterire);
    }

}
