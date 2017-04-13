#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <department.h>
#include <personal.h>
#include <trolleybus.h>

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
    void on_actionDepartment_triggered();
    void on_actionPersonal_triggered();
    void on_actionTrolleybus_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    department *departmentTable;
    personal *personalTable;
    trolleybus *trolleybusTable;
};

#endif // MAINWINDOW_H
