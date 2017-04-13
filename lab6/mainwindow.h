#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QLinearGradient>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void updateRGB(int red, int green, int blue);
    void updateRGBSliderMode(int red, int green, int blue);
    ~MainWindow();

public slots:
    void moveSlider();
    void movePoint();

private:
    Ui::MainWindow *ui;
    QImage *palette;
    QPoint pointer;
    int counter;
};

#endif // MAINWINDOW_H
