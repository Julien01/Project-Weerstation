#include "grafiek.h"
#include "ui_grafiek.h"
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

grafiek::grafiek(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::grafiek)
{
    ui->setupUi(this);

    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("temperature");
    model->select(); // Laad alle gegevens

    // Temperatuur serie en grafiek
    QLineSeries *tempSeries = new QLineSeries();
    for (int row = 0; row < model->rowCount(); ++row) {
        double temperature = model->data(model->index(row, 1)).toDouble(); // Temperatuur
        QDateTime timestamp = model->data(model->index(row, 4)).toDateTime(); // Tijdstip
        tempSeries->append(timestamp.toMSecsSinceEpoch(), temperature);
    }
    QChart *tempChart = new QChart();
    tempChart->legend()->hide();
    tempChart->addSeries(tempSeries);
    QDateTimeAxis *tempAxisX = new QDateTimeAxis();
    tempAxisX->setFormat("hh:mm");
    QDateTime minTempTime = model->data(model->index(0, 4)).toDateTime();
    QDateTime maxTempTime = model->data(model->index(model->rowCount() - 1, 4)).toDateTime();
    tempAxisX->setRange(minTempTime, maxTempTime);
    tempChart->addAxis(tempAxisX, Qt::AlignBottom);
    tempSeries->attachAxis(tempAxisX);
    QValueAxis *tempAxisY = new QValueAxis();
    tempAxisY->setTitleText("Temperatuur (°C)");
    tempAxisY->setRange(0, 30);
    tempChart->addAxis(tempAxisY, Qt::AlignLeft);
    tempSeries->attachAxis(tempAxisY);
    QChartView *tempChartView = new QChartView(tempChart);
    tempChartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalWidgetTemp->layout()->addWidget(tempChartView);

    // Luchtvochtigheid serie en grafiek
    QLineSeries *humSeries = new QLineSeries();
    for (int row = 0; row < model->rowCount(); ++row) {
        double humidity = model->data(model->index(row, 2)).toDouble(); // Luchtvochtigheid
        QDateTime timestamp = model->data(model->index(row, 4)).toDateTime(); // Tijdstip
        humSeries->append(timestamp.toMSecsSinceEpoch(), humidity);
    }
    QChart *humChart = new QChart();
    humChart->legend()->hide();
    humChart->addSeries(humSeries);
    QDateTimeAxis *humAxisX = new QDateTimeAxis();
    humAxisX->setFormat("hh:mm");
    humAxisX->setRange(minTempTime, maxTempTime);
    humChart->addAxis(humAxisX, Qt::AlignBottom);
    humSeries->attachAxis(humAxisX);
    QValueAxis *humAxisY = new QValueAxis();
    humAxisY->setTitleText("Luchtvochtigheid (%)");
    humAxisY->setRange(0, 100);
    humChart->addAxis(humAxisY, Qt::AlignLeft);
    humSeries->attachAxis(humAxisY);
    QChartView *humChartView = new QChartView(humChart);
    humChartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalWidgetHum->layout()->addWidget(humChartView);

    // Druk serie en grafiek
    QLineSeries *presSeries = new QLineSeries();
    for (int row = 0; row < model->rowCount(); ++row) {
        double pressure = model->data(model->index(row, 3)).toDouble(); // Druk
        QDateTime timestamp = model->data(model->index(row, 4)).toDateTime(); // Tijdstip
        presSeries->append(timestamp.toMSecsSinceEpoch(), pressure);
    }
    QChart *presChart = new QChart();
    presChart->legend()->hide();
    presChart->addSeries(presSeries);
    QDateTimeAxis *presAxisX = new QDateTimeAxis();
    presAxisX->setFormat("hh:mm");
    presAxisX->setRange(minTempTime, maxTempTime);
    presChart->addAxis(presAxisX, Qt::AlignBottom);
    presSeries->attachAxis(presAxisX);
    QValueAxis *presAxisY = new QValueAxis();
    presAxisY->setTitleText("Druk (hPa)");
    presAxisY->setRange(0, 150);
    presChart->addAxis(presAxisY, Qt::AlignLeft);
    presSeries->attachAxis(presAxisY);
    QChartView *presChartView = new QChartView(presChart);
    presChartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalWidgetPres->layout()->addWidget(presChartView);
}

grafiek::~grafiek()
{
    delete ui;
}

void grafiek::on_pushButton_clicked()
{
    close();
}
