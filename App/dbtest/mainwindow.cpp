#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include "datatabel.h"
#include "grafiek.h"
#include "temperatuur.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(950, 550);
    this->setWindowTitle("Homescreen");

    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("metingen");

    // Pas de filter aan om alleen de meest recente rij op te halen
    model->setFilter("tijd = (SELECT MAX(tijd) FROM metingen)");
    model->select(); // Laad de gegevens

    // Stel het model in op de QTableView
    ui->Recent->setModel(model);
    ui->Recent->hideColumn(0); // Verberg tabel kolom ID
    ui->Recent->verticalHeader()->setVisible(false); // Rij nummers verbergen

    model->setHeaderData(4, Qt::Horizontal, tr("Tijdstip"));
    model->setHeaderData(1, Qt::Horizontal, tr("Temperatuur"));
    model->setHeaderData(2, Qt::Horizontal, tr("Luchtvochtigheid"));
    model->setHeaderData(3, Qt::Horizontal, tr("Luchtdruk"));

    ui->Recent->setColumnWidth(4, 170); // Maak tijdstip kolom breder

    // Stel een QTimer in om de tabel regelmatig te verversen
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updateModel);
    updateTimer->start(5000); // Ververs elke 5 sec
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateModel()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(ui->Recent->model());
    if (model) {
        model->select(); // Vernieuw het model om nieuwe gegevens op te halen
    }
}

void MainWindow::on_pushButton_clicked()
{
    DataTabel q; // Maak een instantie van DataTabel
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
