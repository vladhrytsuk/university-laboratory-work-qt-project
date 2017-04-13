#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <order.h>
#include <client.h>
#include <employee.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool connectDB(QString name);
    ~MainWindow();

public slots:
    void on_actionOrder_triggered();
    void on_actionClient_triggered();
    void on_actionEmployee_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    order *orderTable;
    client *clientTable;
    employee *employeeTable;
};

#endif // MAINWINDOW_H
