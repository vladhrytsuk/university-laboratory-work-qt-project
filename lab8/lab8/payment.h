#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDialog>

#include <QMessageBox>

namespace Ui {
class Payment;
}

class Payment : public QDialog
{
    Q_OBJECT

public:
    explicit Payment(QWidget *parent = 0);
    ~Payment();

private slots:
    void on_payButton_clicked();

private:
    Ui::Payment *ui;
};

#endif // PAYMENT_H
