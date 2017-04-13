#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QString path = QFileDialog::getOpenFileName(this, "Open DataBase", "", "DataBase Documents (*.sqlite)");
    connectDB(path);

    orderTable = new order(db);
    clientTable = new client(db);
    employeeTable = new employee(db);

    on_actionClient_triggered();
    on_actionEmployee_triggered();
    on_actionOrder_triggered();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOrder_triggered() {
    ui->verticalLayout->removeWidget(clientTable);
    clientTable->hide();
    ui->verticalLayout->removeWidget(employeeTable);
    employeeTable->hide();

    orderTable->setHidden(false);
    ui->horizontalLayout->addWidget(orderTable);
}

void MainWindow::on_actionClient_triggered() {
    ui->verticalLayout->removeWidget(orderTable);
    orderTable->hide();
    ui->verticalLayout->removeWidget(employeeTable);
    employeeTable->hide();

    clientTable->setHidden(false);
    ui->horizontalLayout->addWidget(clientTable);
}

void MainWindow::on_actionEmployee_triggered() {
    ui->verticalLayout->removeWidget(orderTable);
    orderTable->hide();
    ui->verticalLayout->removeWidget(clientTable);
    clientTable->hide();

    employeeTable->setHidden(false);
    ui->horizontalLayout->addWidget(employeeTable);
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
