#ifndef TROLLEYBUS_H
#define TROLLEYBUS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QFileDialog>
#include <QBuffer>

namespace Ui {
    class trolleybus;
}

class trolleybus : public QWidget {
    Q_OBJECT

public:
    explicit trolleybus(QSqlDatabase db, QWidget *parent = 0);
    ~trolleybus();

public slots:
    void addNote();
    void deleteNote();
    void showTrolleybusPhoto(const QModelIndex &index);
    void saveTrolleybusPhoto();

private:
    Ui::trolleybus *ui;
    QSqlRelationalTableModel *tableModel;
};
#endif // TROLLEYBUS_H
