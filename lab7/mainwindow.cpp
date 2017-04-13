#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString path = QFileDialog::getOpenFileName(this, "Open DataBase", "", "DataBase Documents (*.sqlite)");
    connectDB(path);

    productTable = new Product(db);
    customerTable = new Customer(db);
    buyerOfGoodsTable = new BuyerOfGoods(db);

    on_actionCustomer_triggered();
    on_actionProduct_triggered();
    on_actionBuyerOfGoods_triggered();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionProduct_triggered()
{
    ui->verticalLayout->removeWidget(customerTable);
    customerTable->hide();
    ui->verticalLayout->removeWidget(buyerOfGoodsTable);
    buyerOfGoodsTable->hide();

    productTable->setHidden(false);
    ui->horizontalLayout->addWidget(productTable);
}

void MainWindow::on_actionCustomer_triggered()
{
    ui->verticalLayout->removeWidget(productTable);
    productTable->hide();
    ui->verticalLayout->removeWidget(buyerOfGoodsTable);
    buyerOfGoodsTable->hide();

    customerTable->setHidden(false);
    ui->horizontalLayout->addWidget(customerTable);
}

void MainWindow::on_actionBuyerOfGoods_triggered()
{
    ui->verticalLayout->removeWidget(productTable);
    productTable->hide();
    ui->verticalLayout->removeWidget(customerTable);
    customerTable->hide();

    buyerOfGoodsTable->setHidden(false);
    ui->horizontalLayout->addWidget(buyerOfGoodsTable);
}

bool MainWindow::connectDB(QString name)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);
    if (!db.open()) {
        QMessageBox::warning(this, "Error", "Unable to access the database");
        return false;
    }
    return true;
}
