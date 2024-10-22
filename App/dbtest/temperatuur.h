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


private:
    Ui::temperatuur *ui;
};

#endif // TEMPERATUUR_H
