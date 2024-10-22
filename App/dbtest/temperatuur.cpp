#include "temperatuur.h"
#include "ui_temperatuur.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QBoxLayout>
#include <QDateTime>
#include <QTimer>

temperatuur::temperatuur(QWidget *parent)
    : QDialog(parent), ui(new Ui::temperatuur)
{
    ui->setupUi(this);

    this->setFixedSize(1200,550);
    this->setWindowTitle("Temperatuur");

    // Model instellen voor de tabel 'metingen'
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("metingen");
    //model->setFilter("tijd >= NOW() - INTERVAL 1 DAY"); nu en 24 uur geleden
    model->setFilter("tijd >= (SELECT MAX(tijd) FROM metingen) - INTERVAL 1 DAY"); //vanaf laatste meting tot 24 uur geleden
    model->select(); // Laad alle gegevens

    ui->Temp->setModel(model);
    ui->Temp->hideColumn(0); // Verberg ID-kolom
    ui->Temp->hideColumn(2); // Verberg Humidity-kolom
    ui->Temp->hideColumn(3); // Verberg Pressure-kolom
    ui->Temp->verticalHeader()->setVisible(false); // Verberg rij nummers

    // Pas headers aan
    model->setHeaderData(4, Qt::Horizontal, tr("Tijdstip"));
    model->setHeaderData(1, Qt::Horizontal, tr("Temperatuur"));
    ui->Temp->setColumnWidth(4, 170); // Maak tijdstip kolom breder

    // Maak een apart model voor de label
    QSqlTableModel *model2 = new QSqlTableModel(this);
    model2->setTable("metingen");
    model2->setFilter("tijd = (SELECT MAX(tijd) FROM metingen)"); // Filter voor max tijd
    model2->select(); // Laad gegevens met filter

    QString latestDate = model2->data(model2->index(0, 4)).toString(); // Neem de max datum
    ui->labeldate->setText(latestDate); // Stel de tekst van een QLabel in


    QLineSeries *series = new QLineSeries();

    // Vul de series met data uit het model van de eerste tabel
    for (int row = 0; row < model->rowCount(); ++row) {
        QString tempString = model->data(model->index(row, 1)).toString().trimmed();
        tempString = tempString.split(" ").first(); // Haal alleen het numerieke deel voor de "°C"

        bool ok;
        double temperature = tempString.toDouble(&ok);

        QDateTime timestamp = model->data(model->index(row, 4)).toDateTime(); // Tijdstip
        series->append(timestamp.toMSecsSinceEpoch(), temperature);

    }

    // Maak een grafiek en voeg de serie toe
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    // Pas de X-as aan naar QDateTimeAxis
    QDateTimeAxis *axisX = new QDateTimeAxis();
    axisX->setFormat("hh:mm"); // Weergeven als uren en minuten

    // Stel het bereik van de X-as in op basis van je data
    QDateTime minTime = model->data(model->index(0, 4)).toDateTime(); // Eerste tijdstip
    QDateTime maxTime = model->data(model->index(model->rowCount() - 1, 4)).toDateTime(); // Laatste tijdstip
    axisX->setRange(minTime, maxTime); // Bereik van de tijd as instellen

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Y-as blijft een QValueAxis en wordt ingesteld van 0 tot 30
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Temperatuur (°C)");
    axisY->setRange(0, 30); // Stel het bereik van de Y-as in
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Maak een QChartView om de grafiek weer te geven
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setVisible(true);

    ui->verticalLayout->addWidget(chartview);

    // Stel een QTimer in om de tabel regelmatig te verversen
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &temperatuur::updateModel);
    updateTimer->start(5000); // Ververs elke 5 sec
}

void temperatuur::updateModel()
{
    QSqlTableModel *model = qobject_cast<QSqlTableModel *>(ui->Temp->model());
    if (model) {
        model->select(); // Vernieuw het model om nieuwe gegevens op te halen
    }
}

temperatuur::~temperatuur()
{
    delete ui;
}

void temperatuur::on_pushButton_clicked()
{
    close();
}




