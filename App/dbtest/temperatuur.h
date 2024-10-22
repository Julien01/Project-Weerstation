#ifndef TEMPERATUUR_H
#define TEMPERATUUR_H

#include <QDialog>

#include <QtCore>
#include <Qtgui>
#include <Qtcharts>


namespace Ui {
class temperatuur;
}

class temperatuur : public QDialog
{
    Q_OBJECT

public:
    explicit temperatuur(QWidget *parent = nullptr);
    ~temperatuur();

private slots:
    void on_pushButton_clicked();
    void updateModel();


private:
    Ui::temperatuur *ui;
    QTimer *updateTimer;
};

#endif // TEMPERATUUR_H
