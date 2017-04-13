#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

namespace Ui {
    class department;
}

class department : public QWidget {
    Q_OBJECT

public:
    explicit department(QSqlDatabase db, QWidget *parent = 0);
    ~department();

public slots:
    void addNote();
    void deleteNote();

private:
    Ui::department *ui;
    QSqlRelationalTableModel *tableModel;
};

#endif // DEPARTMENT_H
