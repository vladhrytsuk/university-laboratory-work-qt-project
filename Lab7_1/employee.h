#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

namespace Ui {
    class employee;
}

class employee : public QWidget {
    Q_OBJECT

public:
    explicit employee(QSqlDatabase db, QWidget *parent = 0);
    ~employee();

public slots:
    void addNote();
    void deleteNote();

private:
    Ui::employee *ui;
    QSqlRelationalTableModel *tableModel;
};

#endif // EMPLOYEE_H
