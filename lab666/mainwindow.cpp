#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    height = this->width();
    qDebug() << height;
    radius = 40;
    a = 150;
    point.setX(0); // Задаем начальную координату окружности по оси Х
    point.setY(8 * (pow(a, 3)) / (pow(point.x(), 2) + 4 * pow(a, 2)));
    timer = new QTimer(this);
    // Обновляем рисунок с каждой секундой
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));

    QHBoxLayout *layout = new QHBoxLayout(this);
    connect(stop,SIGNAL(clicked()),timer,SLOT(stop()));
    layout->addWidget(stop);
    setLayout(layout);

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QFont f("Century Gothic", 12);
    painter.setFont(f);
    painter.rotate(270);
    painter.drawText(-250,20,tr("graphics in libs QT"));
    painter.rotate(-270);
    painter.setBrush(QBrush(Qt::red,Qt::Dense7Pattern));
    painter.setPen(QPen(Qt::red,1,Qt::SolidLine));
    // Рисуем три круга треугольником
        painter.drawEllipse(point.x(), point.y(), radius, radius);
        painter.drawEllipse(point.x() + radius, point.y(), radius, radius);
        painter.drawEllipse(point.x() + radius / 2, point.y() - radius/1.2, radius, radius);
        // Прописываем координаты движения
        if(point.x() < height){
                point.setX(point.x() + 10);
                point.setY(8 * (pow(a, 3)) / (pow(point.x(), 2) + 4 * pow(a, 2)) );    }
        else{
                point.setX(0);
                point.setY(8 * (pow(a, 3)) / (pow(point.x(), 2) + 4 * pow(a, 2)) );   }
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->MouseButtonPress)
    timer->start(50);

}
