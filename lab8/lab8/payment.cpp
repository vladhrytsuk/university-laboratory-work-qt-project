#include "payment.h"
#include "ui_payment.h"

Payment::Payment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);

    connect(ui->payButton, SIGNAL(clicked()), this, SLOT(accept()));
}

Payment::~Payment()
{
    delete ui;
}

void Payment::on_payButton_clicked()
{
    QMessageBox::information(this, tr("Уведомление"), tr("Оплата успешно произведена"));
}
