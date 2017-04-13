#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include "registration.h"
#include "coursecatalog.h"
#include "viewdescription.h"
#include "registration.h"
#include "payment.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_loginButton_clicked();

    void on_registrationButton_clicked();

private:
    Ui::MainWindow *ui;
    Registration *registration;
    CourseCatalog *courseCatalog;
    ViewDescription *viewDescription;
    Payment *payment;
};

#endif // MAINWINDOW_H
