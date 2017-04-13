#include "mypainter.h"
#include "ui_mypainter.h"

MyPainter::MyPainter(QWidget *parent): QMainWindow(parent), ui(new Ui::MyPainter) {
    ui->setupUi(this);
}

MyPainter::~MyPainter() {
    delete ui;
}

int MyPainter::sing(int x) {
    return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

void MyPainter::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    int x1 = 150, y1 = 200, x2 = 250, y2 = 200;
    drawLinear(x1, y1, x2, y2);

    int radius = 50;
    x1 = 200, y1 = 300;
    circleDraw(x1, y1, radius);
}

//---------------------------------------
//рисование линии
//---------------------------------------
void MyPainter::drawLinear(int x1, int y1, int x2, int y2) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 2));

    int x, y, dx, dy, incx, incy, pdx, pdy, es, el, err;

    dx = x2 - x1;//проекция на х
    dy = y2 - y1;//на у

    incx = sing(dx);//если в противоположную сторону от координат (направления) рисуем
    incy = sing(dy);

    dx = abs(dx);
    dy = abs(dy);

    if (dx > dy) {//вдоль х
        pdx = incx;
        pdy = 0;
        es = dy;
        el = dx;
    } else {//вдоль у
        pdx = 0;
        pdy = incy;
        es = dx;
        el = dy;
    }

    x = x1;
    y = y1;
    err = el/2;
    painter.drawPoint(x, y);

    for (int t = 0; t < el; t++)
    {
        err -= es;
        if (err < 0) {
            err += el;
            x += incx;
            y += incy;
        }
        else {
            x += pdx;
            y += pdy;
        }
        painter.drawPoint(x, y);
    }
}

//---------------------------------------
//рисование окружнасти
//---------------------------------------
void MyPainter::circleDraw(int x0, int y0, int radius) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::blue, 2));

    int x = 0;
    int D = 3 - 2 * radius;

    while (x <= radius) {
        painter.drawPoint(x + x0, radius + y0);
        painter.drawPoint(radius + x0, x + y0);
        painter.drawPoint(-x + x0, radius + y0);
        painter.drawPoint(-radius + x0, x + y0);
        painter.drawPoint(-x + x0, -radius + y0);
        painter.drawPoint(-radius + x0, -x + y0);
        painter.drawPoint(x + x0, -radius + y0);
        painter.drawPoint(radius + x0, -x + y0);
        x++;

        if (D < 0) {
            D += 4 * x + 6;
        } else {
            radius--;
            D += 4 * (x - radius) + 10;
        }

    }
}


