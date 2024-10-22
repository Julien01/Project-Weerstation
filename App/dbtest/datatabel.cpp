#include "datatabel.h"
#include "ui_datatabel.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QTimer>

DataTabel::DataTabel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataTabel)
{
    ui->setupUi(this);

    this->setFixedSize(950,650);
    this->setWindowTitle("Alle data");

    // Maak een model voor de metingen-tabel
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("metingen");
    model->setFilter("tijd >= (SELECT MAX(tijd) FROM metingen) - INTERVAL 1 DAY"); //vanaf laatste meting tot 24 uur geleden
    //model->setFilter("tijd >= NOW() - INTERVAL 1 DAY"); nu en 24 uur geleden
    model->select(); // Laad de gegevens

    // Stel het model in op de QTableView
    ui->Temp->setModel(model);

    ui->Temp->hideColumn(0);//verbergt tabel kolom ID
    ui->Temp->verticalHeader()->setVisible(false);//rij nummers uit

    // (Optioneel) Pas de weergave-instellingen aan
    model->setHeaderData(4, Qt::Horizontal, tr("Tijdstip"));
    model->setHeaderData(1, Qt::Horizontal, tr("Temperatuur")); // eerste kolom
    model->setHeaderData(2, Qt::Horizontal, tr("Luchtvochtigheid"));
    model->setHeaderData(3, Qt::Horizontal, tr("Luchtdruk"));

    ui->Temp->setColumnWidth(4, 170);//maak tijdstip breeder

    // Stel een QTimer in om de tabel regelmatig te verversen
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &DataTabel::updateModel);
    updateTimer->start(5000); // Ververs elke 5 sec


}

void DataTabel::updateModel()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(ui->Temp->model());
    if (model) {
        model->select(); // Vernieuw het model om nieuwe gegevens op te halen
    }
}

DataTabel::~DataTabel()
{
    delete ui;
}

void DataTabel::on_pushButton_clicked()
{
    close();
}

