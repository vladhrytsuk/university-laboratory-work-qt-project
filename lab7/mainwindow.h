#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <product.h>
#include <customer.h>
#include <buyerofgoods.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool connectDB(QString name);
    ~MainWindow();

public slots:
    void on_actionProduct_triggered();
    void on_actionCustomer_triggered();
    void on_actionBuyerOfGoods_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    Product *productTable;
    Customer *customerTable;
    BuyerOfGoods *buyerOfGoodsTable;
};

#endif // MAINWINDOW_H
