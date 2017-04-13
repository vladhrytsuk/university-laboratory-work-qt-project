#include "personal.h"
#include "ui_personal.h"

personal::personal(QSqlDatabase db, QWidget *parent): QWidget(parent), ui(new Ui::personal) {
    ui->setupUi(this);

    tableModel = new QSqlRelationalTableModel(this, db);

    if (db.isOpen()) {
        tableModel->setTable("Personal");
        tableModel->setHeaderData(0, Qt::Horizontal, "id");
        tableModel->setHeaderData(1, Qt::Horizontal, "First name");
        tableModel->setHeaderData(2, Qt::Horizontal, "Last name");
        tableModel->setHeaderData(3, Qt::Horizontal, "Phone number");
        tableModel->select();
    }

    ui->tableView->setModel(tableModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(tableModel));

    connect(ui->add, SIGNAL(clicked()), this, SLOT(addNote()));
    connect(ui->delete_2, SIGNAL(clicked()), this, SLOT(deleteNote()));
}

personal::~personal() {
    delete ui;
}


void personal::addNote() {
    QString id = ui->lineId->text();
    QString firstName = ui->lineFirstName->text();
    QString lastName = ui->lineLastName->text();
    QString phoneNumber = ui->linePhoneNumber->text();

    if (id.isEmpty() || firstName.isEmpty() || lastName.isEmpty() || phoneNumber.isEmpty()) {
        QMessageBox::warning(this, "Error", "Fill in all fields");
        return;
    }

    int numOfRows = tableModel->rowCount();
    tableModel->insertRows(numOfRows, 1);
    tableModel->setData(tableModel->index(numOfRows, 0), id.toInt());
    tableModel->setData(tableModel->index(numOfRows, 1), firstName);
    tableModel->setData(tableModel->index(numOfRows, 2), lastName);
    tableModel->setData(tableModel->index(numOfRows, 3), phoneNumber);

    if (!tableModel->submitAll()) {
        QMessageBox::warning(this, "Error", "Operation failed insertion");
        tableModel->removeRow(numOfRows);
        return;
    }

    ui->tableView->setModel(tableModel);
}

void personal::deleteNote() {
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
