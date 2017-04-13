#ifndef PERSONAL_H
#define PERSONAL_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

namespace Ui {
    class personal;
}

class personal : public QWidget {
    Q_OBJECT

public:
    explicit personal(QSqlDatabase db, QWidget *parent = 0);
    ~personal();

public slots:
    void addNote();
    void deleteNote();

private:
    Ui::personal *ui;
    QSqlRelationalTableModel *tableModel;
};

#endif // PERSONAL_H
