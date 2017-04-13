#include "trolleybus.h"
#include "ui_trolleybus.h"

trolleybus::trolleybus(QSqlDatabase db, QWidget *parent): QWidget(parent), ui(new Ui::trolleybus) {
    ui->setupUi(this);

    tableModel = new QSqlRelationalTableModel(this, db);

    if (db.isOpen()) {
        tableModel->setTable("trolleybus");
        tableModel->setHeaderData(0, Qt::Horizontal, "id");
        tableModel->setHeaderData(1, Qt::Horizontal, "number");
        tableModel->setHeaderData(2, Qt::Horizontal, "photo");
        tableModel->select();
    }

    ui->tableView->setModel(tableModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(tableModel));
    ui->tableView->hideColumn(2);

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(showTrolleybusPhoto(const QModelIndex &)));
    connect(ui->add, SIGNAL(clicked()), this, SLOT(addNote()));
    connect(ui->delete_2, SIGNAL(clicked()), this, SLOT(deleteNote()));
    connect(ui->choose, SIGNAL(clicked()), this, SLOT(saveTrolleybusPhoto()));
}

trolleybus::~trolleybus() {
    delete ui;
}

void trolleybus::addNote() {
    QString id = ui->lineId->text();
    QString number = ui->lineNumber->text();
    QString photo = ui->linePhoto->text();

    if (id.isEmpty() || number.isEmpty() || photo.isEmpty()) {
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
    query->prepare("INSERT INTO trolleybus (id,number,photo) "
                   "VALUES (:id, :number, :photo)");
    query->bindValue(":id", id.toInt());
    query->bindValue(":number", number.toInt());
    query->bindValue(":photo", bytes);
    query->exec();

    tableModel->setTable("Order");
    tableModel->setHeaderData(0, Qt::Horizontal, "id");
    tableModel->setHeaderData(1, Qt::Horizontal, "number");
    tableModel->setHeaderData(2, Qt::Horizontal, "photo");
    tableModel->select();

    ui->tableView->setModel(tableModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(tableModel));
    ui->tableView->hideColumn(2);

    int numOfRows = tableModel->rowCount();

    if (!tableModel->submitAll()) {
        QMessageBox::warning(this, "Error", "Operation failed insertion");
        tableModel->removeRow(numOfRows);
        return;
    }
    ui->tableView->setModel(tableModel);
}

void trolleybus::deleteNote() {
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

void trolleybus::showTrolleybusPhoto(const QModelIndex &index) {
    QSqlRecord record = tableModel->record(index.row());
    QSqlQuery query;
    QString str_insert = "SELECT photo FROM trolleybus WHERE id = '%1';";
    QString str = str_insert.arg(record.value("id").toInt());

    bool result = query.exec(str);
    if (!result) {
        QMessageBox::warning(this, "Error", "Issue a request to the table trolleybus");
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
        QMessageBox::warning(this, "Error", "Problem loading photos from the table trolleybus");
        return;
    }
}

void trolleybus::saveTrolleybusPhoto() {
    QString path = QFileDialog::getOpenFileName(this, "Select image", "", "");
    ui->linePhoto->setText(path);
}
