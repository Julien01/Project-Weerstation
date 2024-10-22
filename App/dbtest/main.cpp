#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QBoxLayout>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("weerstation.jarnejanssen.nl");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("poepjepoepje");
    db.setDatabaseName("projectweerstation");

    if (!db.open()) {
        qDebug() << "Error: Unable to open database." << db.lastError().text();
    }

    MainWindow w;
    w.show();

    return a.exec();
}

