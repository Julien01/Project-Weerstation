#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QBoxLayout>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1"); // Corrigeer de hostnaam
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("project_test");

    if (!db.open()) {
        qDebug() << "Error: Unable to open database." << db.lastError().text();
    }

    MainWindow w;
    w.show();

    return a.exec();
}

