#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QMainWindow>
#include <QPainter>
#include <math.h>

namespace Ui {
class MyPainter;
}

class MyPainter : public QMainWindow {
    Q_OBJECT

public:
    explicit MyPainter(QWidget *parent = 0);
    ~MyPainter();

private:
    Ui::MyPainter *ui;
    int sing(int x);
protected:
    void paintEvent(QPaintEvent *event);
    void drawLinear(int x1, int y1, int x2, int y2);
    void circleDraw(int x0, int y0, int radius);
};

#endif // MYPAINTER_H
