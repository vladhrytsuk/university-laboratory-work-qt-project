#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString path = QFileDialog::getOpenFileName(this, "Open DataBase", "", "DataBase Documents (*.sqlite)");
    connectDB(path);

    departmentTable = new department(db);
    personalTable = new personal(db);
    trolleybusTable = new trolleybus(db);

    on_actionDepartment_triggered();
    on_actionPersonal_triggered();
    on_actionTrolleybus_triggered();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDepartment_triggered() {
    ui->verticalLayout->removeWidget(personalTable);
    personalTable->hide();
    ui->verticalLayout->removeWidget(trolleybusTable);
    trolleybusTable->hide();

    departmentTable->setHidden(false);
    ui->horizontalLayout->addWidget(departmentTable);
}

void MainWindow::on_actionPersonal_triggered() {
    ui->verticalLayout->removeWidget(departmentTable);
    departmentTable->hide();
    ui->verticalLayout->removeWidget(trolleybusTable);
    trolleybusTable->hide();

    personalTable->setHidden(false);
    ui->horizontalLayout->addWidget(personalTable);
}

void MainWindow::on_actionTrolleybus_triggered() {
    ui->verticalLayout->removeWidget(personalTable);
    personalTable->hide();
    ui->verticalLayout->removeWidget(departmentTable);
    departmentTable->hide();

    trolleybusTable->setHidden(false);
    ui->horizontalLayout->addWidget(trolleybusTable);
}

bool MainWindow::connectDB(QString name) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);
    if (!db.open()) {
        QMessageBox::warning(this, "Error", "Unable to access the database");
        return false;
    }
    return true;
}
