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

    this->setFixedSize(950,750);
    this->setWindowTitle("Grafieken");

    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("metingen");
    //model->setFilter("tijd >= NOW() - INTERVAL 1 DAY"); nu en 24 uur geleden
    model->setFilter("tijd >= (SELECT MAX(tijd) FROM metingen) - INTERVAL 1 DAY"); //vanaf laatste meting tot 24 uur geleden
    model->select(); // Laad alle gegevens

    // Temperatuur serie en grafiek
    QLineSeries *tempSeries = new QLineSeries();
    for (int row = 0; row < model->rowCount(); ++row) {
        QString tempString = model->data(model->index(row, 1)).toString().trimmed();
        tempString = tempString.split(" ").first(); // Haal alleen het numerieke deel voor de "°C"

        bool ok;
        double temperature = tempString.toDouble(&ok);

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
        QString humString = model->data(model->index(row, 2)).toString().trimmed();
        humString = humString.split(" ").first(); // Haal alleen het numerieke deel voor de "%"

        bool ok;
        double humidity = humString.toDouble(&ok);

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
        QString presString = model->data(model->index(row, 3)).toString().trimmed();
        presString = presString.split(" ").first(); // Haal alleen het numerieke deel voor de "mPa"

        bool ok;
        double pressure = presString.toDouble(&ok);

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
    presAxisY->setTitleText("Druk (mPa)");
    presAxisY->setRange(101400, 101550);
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
