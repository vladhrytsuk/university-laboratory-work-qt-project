#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow();
    QPushButton *Button1, *Button2, *Button3, *Button4, *Button5, *Button6, *Button7, *Button8, *Button9;
    QPushButton *pb[9];
public slots:
    void push(int i);
    void push1();
    void push2();
    void push3();
    void push4();
    void push5();
    void push6();
    void push7();
    void push8();
    void push9();
};

#endif // MAINWINDOW_H
