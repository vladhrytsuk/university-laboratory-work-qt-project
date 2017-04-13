#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <math.h>
#include <QMouseEvent>
#include <QFont>
#include <QString>
#include <QHBoxLayout>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);
    int radius;
    QPoint point;
    int a;
    void mousePressEvent(QMouseEvent *mouseEvent);
    QTimer *timer;

private:
    QPushButton *stop = new QPushButton("Stop",this);



};
#endif // MAINWINDOW_H
