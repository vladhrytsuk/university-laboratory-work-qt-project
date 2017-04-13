#ifndef BUYEROFGOODS_H
#define BUYEROFGOODS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include <QSqlRecord>

namespace Ui {
class BuyerOfGoods;
}

class BuyerOfGoods : public QWidget
{
    Q_OBJECT

public:
    explicit BuyerOfGoods(QSqlDatabase db, QWidget *parent = 0);
    ~BuyerOfGoods();

public slots:
    void addNote();
    void deleteNote();
    void calculate();

private:
    Ui::BuyerOfGoods *ui;
    QSqlRelationalTableModel *tableModel;
    QSqlRelationalTableModel *productModel;

};

#endif // BUYEROFGOODS_H
