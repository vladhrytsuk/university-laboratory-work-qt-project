#include "customer.h"
#include "ui_customer.h"

Customer::Customer(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Customer)
{
    ui->setupUi(this);
    tableModel = new QSqlRelationalTableModel(this, db);

    if (db.isOpen()) {
        tableModel->setTable("Customer");
        tableModel->setHeaderData(0, Qt::Horizontal, "Customer code");
        tableModel->setHeaderData(1, Qt::Horizontal, "First name");
        tableModel->setHeaderData(2, Qt::Horizontal, "Last name");
        tableModel->setHeaderData(3, Qt::Horizontal, "Phone number");
        tableModel->select();
    }

    ui->tableView->setModel(tableModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(tableModel));

    connect(ui->buttonAdd, SIGNAL(clicked()), this, SLOT(addNote()));
    connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteNote()));
}

Customer::~Customer()
{
    delete ui;
}

void Customer::addNote()
{
    QString custCode = ui->lineEdit->text();
    QString fName = ui->lineEdit_2->text();
    QString lName = ui->lineEdit_3->text();
    QString phone = ui->lineEdit_4->text();

    if (custCode.isEmpty() || fName.isEmpty() || lName.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "Error", "Fill in all fields");
        return;
    }

    int numOfRows = tableModel->rowCount();
    tableModel->insertRows(numOfRows, 1);
    tableModel->setData(tableModel->index(numOfRows, 0), custCode.toInt());
    tableModel->setData(tableModel->index(numOfRows, 1), fName);
    tableModel->setData(tableModel->index(numOfRows, 2), lName);
    tableModel->setData(tableModel->index(numOfRows, 3), phone);

    if (!tableModel->submitAll()) {
        QMessageBox::warning(this, "Error", "Operation failed insertion");
        tableModel->removeRow(numOfRows);
        return;
    }
    ui->tableView->setModel(tableModel);
}

void Customer::deleteNote()
{
    int count = ui->tableView->selectionModel()->selectedRows().count();
    if (count == 0) {
        QMessageBox::warning(this, "Error", "Choose field for delete");
        return;
    }

    for (int i = 0; i < count; ++i) {
        tableModel->removeRow(ui->tableView->selectionModel()->selectedRows().at(i).row());
        ui->tableView->hideRow(ui->tableView->selectionModel()->selectedRows().at(i).row());
    }

    if (!tableModel->submitAll()) {
        QMessageBox::warning(this, "Error", "Operation failed deleting");
        return;
    }
    ui->tableView->setModel(tableModel);
}
