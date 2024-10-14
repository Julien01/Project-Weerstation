#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include "datatabel.h"
#include "grafiek.h"
#include "temperatuur.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlTableModel *model = new QSqlTableModel(this);

    model->setTable("temperature");

    // Pas de filter aan om alleen de meest recente rij op te halen
    model->setFilter("tijd = (SELECT MAX(tijd) FROM temperature)");
    model->select(); // Laad de gegevens

    // Stel het model in op de QTableView
    ui->Recent->setModel(model);

    ui->Recent->hideColumn(0);//verbergt tabel kolom ID
    ui->Recent->verticalHeader()->setVisible(false);//rij nummers uit

    model->setHeaderData(4, Qt::Horizontal, tr("Tijdstip"));
    model->setHeaderData(1, Qt::Horizontal, tr("Temperatuur"));
    model->setHeaderData(2, Qt::Horizontal, tr("Luchtvochtigheid"));
    model->setHeaderData(3, Qt::Horizontal, tr("Luchtdruk"));

    ui->Recent->setColumnWidth(4, 170);//maak tijdstip breeder

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    DataTabel q; // Maak een instantie van datatabel
    q.show();
    q.exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    temperatuur q; // Maak een instantie van temperatuur
    q.show();
    q.exec();
}


void MainWindow::on_pushButton_3_clicked()
{
    close();
}



void MainWindow::on_pushButton_4_clicked()
{
    grafiek q; // Maak een instantie van grafiek
    q.show();
    q.exec();
}

