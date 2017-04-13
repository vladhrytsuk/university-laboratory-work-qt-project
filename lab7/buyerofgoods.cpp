#include "buyerofgoods.h"
#include "ui_buyerofgoods.h"

#include <QDebug>

BuyerOfGoods::BuyerOfGoods(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuyerOfGoods)
{
    ui->setupUi(this);

    productModel = new QSqlRelationalTableModel(this, db);

    if (db.isOpen()) {
        productModel->setTable("Product");
        productModel->setHeaderData(0, Qt::Horizontal, "Product code");
        productModel->setHeaderData(1, Qt::Horizontal, "Product name");
        productModel->setHeaderData(2, Qt::Horizontal, "Cost");
        productModel->setHeaderData(3, Qt::Horizontal, "Photo");
        productModel->select();
    }

    tableModel = new QSqlRelationalTableModel(this, db);

    if (db.isOpen()) {
        tableModel->setTable("BuyerOfGoods");
        tableModel->setHeaderData(0, Qt::Horizontal, "Product code");
        tableModel->setHeaderData(1, Qt::Horizontal, "Customer code");
        tableModel->setHeaderData(2, Qt::Horizontal, "Purchase date");
        tableModel->setHeaderData(3, Qt::Horizontal, "Count");
        tableModel->select();
    }

    ui->tableView->setModel(tableModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(tableModel));

    connect(ui->buttonAdd, SIGNAL(clicked()), this, SLOT(addNote()));
    connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteNote()));
    connect(ui->buttonCalc, SIGNAL(clicked()), this, SLOT(calculate()));
}

BuyerOfGoods::~BuyerOfGoods()
{
    delete ui;
}

void BuyerOfGoods::calculate()
{
    //int count = ui->tableView->selectionModel()->selectedRows().count();
    QSqlQuery query;
    int sum = 0, cost = 0;

    QSqlRecord rec = tableModel->record(ui->tableView->currentIndex().row());
    QString sCustomerCode = rec.value(1).toString();
    int customerCode = sCustomerCode.toInt();

    for (int i = 0; i < tableModel->rowCount(); ++i) {
        QSqlRecord record = tableModel->record(i);

        QString field1 = record.value(0).toString();
        int iField1 = field1.toInt();

        QString field2 = record.value(1).toString();
        int iField2 = field2.toInt();

        QString field4 = record.value(3).toString();
        int iField4 = field4.toInt();

       // qDebug() << iField2;

        if (iField2 == customerCode) {
            QString str_insert = "SELECT cost FROM Product WHERE productCode is %1;";
            QString str = str_insert.arg(iField1);
            bool result = query.exec(str);
            if (!result) {
                QMessageBox::warning(this, "Error", "Issue a request to the table Product");
                return;
            }

            while (query.next()) {
                 //qDebug() << str;
                for(int i = 0; i < 3; ++i) {
                    cost = query.value(i).toInt();
                    break;
                }


                break;
            }
            sum += iField4 * cost;
        }

    }

    QString count = "Итого к оплате = " + QString::number(sum);
    QMessageBox::information(this, tr("Оплата"), count);
}

void BuyerOfGoods::addNote()
{
    QString productCode = ui->lineEdit->text();
    QString customerCode = ui->lineEdit_2->text();
    QString purchaseDate = ui->lineEdit_3->text();
    QString count = ui->lineEdit_4->text();

    if (productCode.isEmpty() || customerCode.isEmpty() || purchaseDate.isEmpty() || count.isEmpty()) {
        QMessageBox::warning(this, "Error", "Fill in all fields");
        return;
    }

    int numOfRows = tableModel->rowCount();
    tableModel->insertRows(numOfRows, 1);
    tableModel->setData(tableModel->index(numOfRows, 0), productCode.toInt());
    tableModel->setData(tableModel->index(numOfRows, 1), customerCode.toInt());
    tableModel->setData(tableModel->index(numOfRows, 2), purchaseDate);
    tableModel->setData(tableModel->index(numOfRows, 3), count.toInt());

    if (!tableModel->submitAll()) {
        QMessageBox::warning(this, "Error", "Operation failed insertion");
        tableModel->removeRow(numOfRows);
        return;
    }
    ui->tableView->setModel(tableModel);
}

void BuyerOfGoods::deleteNote()
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
