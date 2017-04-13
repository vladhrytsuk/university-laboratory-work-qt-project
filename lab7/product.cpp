#include "product.h"
#include "ui_product.h"

#include <QDebug>

Product::Product(QSqlDatabase db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Product)
{
    ui->setupUi(this);
    tableModel = new QSqlRelationalTableModel(this, db);

    if (db.isOpen()) {
        tableModel->setTable("Product");
        tableModel->setHeaderData(0, Qt::Horizontal, "Product code");
        tableModel->setHeaderData(1, Qt::Horizontal, "Product name");
        tableModel->setHeaderData(2, Qt::Horizontal, "Cost");
        tableModel->setHeaderData(3, Qt::Horizontal, "Photo");
        tableModel->select();
    }

    ui->tableView->setModel(tableModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(tableModel));
    ui->tableView->hideColumn(3);

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(showProductPhoto(const QModelIndex &)));
    connect(ui->buttonAdd, SIGNAL(clicked()), this, SLOT(addNote()));
    connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteNote()));
    connect(ui->buttonChoosePhoto, SIGNAL(clicked()), this, SLOT(saveProductPhoto()));
}

Product::~Product()
{
    delete ui;
}

void Product::addNote()
{
    QString productCode = ui->lineEdit->text();
    QString productName = ui->lineEdit_2->text();
    QString cost = ui->lineEdit_3->text();
    QString photo = ui->lineEdit_4->text();

    if (productCode.isEmpty() || productName.isEmpty() || cost.isEmpty() || photo.isEmpty()) {
        QMessageBox::warning(this, "Error", "Fill in all fields");
        return;
    }

    QByteArray bytes;
    QBuffer buffer(&bytes);
    QImage image;
    image.load(photo);
    image.save(&buffer, "JPG");

    QSqlQuery *query;
    query = new QSqlQuery;
    query->prepare("INSERT INTO Product (productCode,productName,cost,photo) "
                   "VALUES (:productCode, :productName, :cost, :photo)");
    query->bindValue(":productCode", productCode.toInt());
    query->bindValue(":productName", productName);
    query->bindValue(":cost", cost.toInt());
    query->bindValue(":photo", bytes);
    query->exec();

    tableModel->setTable("Product");
    tableModel->setHeaderData(0, Qt::Horizontal, "Product code");
    tableModel->setHeaderData(1, Qt::Horizontal, "Product name");
    tableModel->setHeaderData(2, Qt::Horizontal, "Cost");
    tableModel->setHeaderData(3, Qt::Horizontal, "Photo");
    tableModel->select();

    ui->tableView->setModel(tableModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(tableModel));
    ui->tableView->hideColumn(3);

    int numOfRows = tableModel->rowCount();

    if (!tableModel->submitAll()) {
        QMessageBox::warning(this, "Error", "Operation failed insertion");
        tableModel->removeRow(numOfRows);
        return;
    }
    ui->tableView->setModel(tableModel);
}

void Product::deleteNote()
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

void Product::showProductPhoto(const QModelIndex &index)
{
    QSqlRecord record = tableModel->record(index.row());
    QSqlQuery query;
    QString str_insert = "SELECT photo FROM Product WHERE productCode is '%1';";
    QString str = str_insert.arg(record.value("productCode").toInt());

    bool result = query.exec(str);
    if (!result) {
        QMessageBox::warning(this, "Error", "Issue a request to the table Product");
        return;
    }
    if (query.isSelect()) {
        query.first();
        QPixmap pix;
        QByteArray arr = query.value(0).toByteArray();
        result = pix.loadFromData(arr);
        if (result) {
            pix = pix.scaled(100, 100, Qt::IgnoreAspectRatio);
            ui->label_photo->setPixmap(pix);
        }
    } else {
        QMessageBox::warning(this, "Error", "Problem loading photos from the table Product");
        return;
    }
}

void Product::saveProductPhoto()
{
    QString path = QFileDialog::getOpenFileName(this, "Select image", "", "");
    ui->lineEdit_4->setText(path);
}
