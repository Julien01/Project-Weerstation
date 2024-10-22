#ifndef DATATABEL_H
#define DATATABEL_H

#include <QDialog>

namespace Ui {
class DataTabel;
}

class DataTabel : public QDialog
{
    Q_OBJECT

public:
    explicit DataTabel(QWidget *parent = nullptr);
    ~DataTabel();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DataTabel *ui;
};

#endif // DATATABEL_H
