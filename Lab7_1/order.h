#ifndef ORDER_H
#define ORDER_H

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
    class order;
}

class order : public QWidget {
    Q_OBJECT

public:
    explicit order(QSqlDatabase db, QWidget *parent = 0);
    ~order();

public slots:
    void addNote();
    void deleteNote();
    void showProductPhoto(const QModelIndex &index);
    void saveProductPhoto();

private:
    Ui::order *ui;
    QSqlRelationalTableModel *tableModel;
};

#endif // ORDER_H
