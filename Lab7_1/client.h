#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

namespace Ui {
    class client;
}

class client : public QWidget {
    Q_OBJECT

public:
    explicit client(QSqlDatabase db, QWidget *parent = 0);
    ~client();

public slots:
    void addNote();
    void deleteNote();

private:
    Ui::client *ui;
    QSqlRelationalTableModel *tableModel;
};

#endif // CLIENT_H
