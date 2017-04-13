#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    registration = new Registration;
    courseCatalog = new CourseCatalog;
    viewDescription = new ViewDescription;
    payment = new Payment;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    QMessageBox::information(this, tr("Уведомление"), tr("Авторизация произошла успешно"));
    courseCatalog->show();
    if (courseCatalog->exec() == QDialog::Accepted) {
        QString fileName = courseCatalog->getCouseName();
        viewDescription->setFileName(fileName);
        viewDescription->setCourseDescription();
        viewDescription->show();
        if (viewDescription->exec() == QDialog::Accepted) {
            payment->show();
        }
    }
}

void MainWindow::on_registrationButton_clicked()
{
    registration->show();
}
