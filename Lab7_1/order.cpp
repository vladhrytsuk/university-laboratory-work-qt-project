#include "order.h"
#include "ui_order.h"

order::order(QSqlDatabase db, QWidget *parent): QWidget(parent), ui(new Ui::order) {
    ui->setupUi(this);

    tableModel = new QSqlRelationalTableModel(this, db);

    if (db.isOpen()) {
        tableModel->setTable("Order");
        tableModel->setHeaderData(0, Qt::Horizontal, "client_id");
        tableModel->setHeaderData(1, Qt::Horizontal, "employee_id");
        tableModel->setHeaderData(2, Qt::Horizontal, "appliances");
        tableModel->setHeaderData(3, Qt::Horizontal, "description");
        tableModel->setHeaderData(4, Qt::Horizontal, "photo");
        tableModel->select();
    }

    ui->tableView->setModel(tableModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(tableModel));
    ui->tableView->hideColumn(4);

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(showProductPhoto(const QModelIndex &)));
    connect(ui->add, SIGNAL(clicked()), this, SLOT(addNote()));
    connect(ui->delete_2, SIGNAL(clicked()), this, SLOT(deleteNote()));
    connect(ui->choose, SIGNAL(clicked()), this, SLOT(saveProductPhoto()));
}

order::~order() {
    delete ui;
}

void order::addNote() {
    QString client_id = ui->lineClient_id->text();
    QString employee_id = ui->lineEmployee_id->text();
    QString appliances = ui->lineAppliances->text();
    QString description = ui->lineDescription->text();
    QString photo = ui->linePhoto->text();

    if (client_id.isEmpty() || employee_id.isEmpty() || appliances.isEmpty() || description.isEmpty()) {
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
    query->prepare("INSERT INTO Order (client_id,employee_id,appliances,description,photo) "
                   "VALUES (:client_id, :employee_id, :appliances, :description, :photo)");
    query->bindValue(":client_id", client_id.toInt());
    query->bindValue(":employee_id", employee_id.toInt());
    query->bindValue(":appliances", appliances);
    query->bindValue(":description", description);
    query->bindValue(":photo", bytes);
    query->exec();

    tableModel->setTable("Order");
    tableModel->setHeaderData(0, Qt::Horizontal, "client_id");
    tableModel->setHeaderData(1, Qt::Horizontal, "employee_id");
    tableModel->setHeaderData(2, Qt::Horizontal, "appliances");
    tableModel->setHeaderData(3, Qt::Horizontal, "description");
    tableModel->setHeaderData(4, Qt::Horizontal, "photo");
    tableModel->select();

    ui->tableView->setModel(tableModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(tableModel));
    ui->tableView->hideColumn(4);

    int numOfRows = tableModel->rowCount();

    if (!tableModel->submitAll()) {
        QMessageBox::warning(this, "Error", "Operation failed insertion");
        tableModel->removeRow(numOfRows);
        return;
    }
    ui->tableView->setModel(tableModel);
}

void order::deleteNote() {
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

void order::showProductPhoto(const QModelIndex &index) {
    QSqlRecord record = tableModel->record(index.row());
    QSqlQuery query;
    QString str_insert = "SELECT photo FROM Order WHERE id = '%1';";
    QString str = str_insert.arg(record.value("id").toInt());

    bool result = query.exec(str);
    if (!result) {
        QMessageBox::warning(this, "Error", "Issue a request to the table Order");
        return;
    }
    if (query.isSelect()) {
        query.first();
        QPixmap pix;
        QByteArray arr = query.value(0).toByteArray();
        result = pix.loadFromData(arr);
        if (result) {
            pix = pix.scaled(100, 100, Qt::IgnoreAspectRatio);
            ui->photo->setPixmap(pix);
        }
    } else {
        QMessageBox::warning(this, "Error", "Problem loading photos from the table Order");
        return;
    }
}

void order::saveProductPhoto() {
    QString path = QFileDialog::getOpenFileName(this, "Select image", "", "");
    ui->linePhoto->setText(path);
}
