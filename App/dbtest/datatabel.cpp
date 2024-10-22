#include "datatabel.h"
#include "ui_datatabel.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>

DataTabel::DataTabel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataTabel)
{
    ui->setupUi(this);

    // Maak een model voor de temperature-tabel
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("temperature");
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


}

DataTabel::~DataTabel()
{
    delete ui;
}

void DataTabel::on_pushButton_clicked()
{
    close();
}

