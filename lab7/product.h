#ifndef PRODUCT_H
#define PRODUCT_H

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
class Product;
}

class Product : public QWidget
{
    Q_OBJECT

public:
    explicit Product(QSqlDatabase db, QWidget *parent = 0);
    ~Product();

public slots:
    void addNote();
    void deleteNote();
    void showProductPhoto(const QModelIndex &index);
    void saveProductPhoto();

private:
    Ui::Product *ui;
    QSqlRelationalTableModel *tableModel;
};

#endif // PRODUCT_H
