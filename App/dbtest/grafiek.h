#ifndef GRAFIEK_H
#define GRAFIEK_H

#include <QDialog>

namespace Ui {
class grafiek;
}

class grafiek : public QDialog
{
    Q_OBJECT

public:
    explicit grafiek(QWidget *parent = nullptr);
    ~grafiek();

private slots:
    void on_pushButton_clicked();

private:
    Ui::grafiek *ui;
};

#endif // GRAFIEK_H
