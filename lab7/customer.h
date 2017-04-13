#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

namespace Ui {
class Customer;
}

class Customer : public QWidget
{
    Q_OBJECT

public:
    explicit Customer(QSqlDatabase db, QWidget *parent = 0);
    ~Customer();

public slots:
    void addNote();
    void deleteNote();

private:
    Ui::Customer *ui;
    QSqlRelationalTableModel *tableModel;
};

#endif // CUSTOMER_H
