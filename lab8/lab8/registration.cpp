#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    connect(ui->resigtrationButton, SIGNAL(clicked()), this, SLOT(accept()));
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_resigtrationButton_clicked()
{
    QString name = tr("Пользователь с именем ") + ui->lineEdit->text() + tr(" успешно зарегистрирован");
    QMessageBox::information(this, tr("Уведомление"), name);
    hide();
}
