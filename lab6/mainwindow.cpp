#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    counter = 0;

    palette = new QImage(ui->labelPalette->size(), QImage::Format_RGB32);
    palette->fill(Qt::white);

    connect(ui->hSlider, SIGNAL(valueChanged(int)), this, SLOT(moveSlider()));
    connect(ui->hSlider_2, SIGNAL(valueChanged(int)), this, SLOT(moveSlider()));
    connect(ui->hSlider_3, SIGNAL(valueChanged(int)), this, SLOT(moveSlider()));

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(movePoint()));
    connect(ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(movePoint()));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(palette);
    QRect rect = ui->labelPalette->geometry();
    QLinearGradient gradient(rect.left(), rect.top(), rect.right(), rect.top());
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(0.33, Qt::green);
    gradient.setColorAt(0.66, Qt::blue);
    gradient.setColorAt(1, Qt::red);
    QBrush brush(gradient);
    painter.fillRect(0, 0, rect.width(), rect.height(), brush);
    painter.drawEllipse(pointer.x() - 5, pointer.y() - 5, 10, 10);
    painter.end();

    ui->labelPalette->setPixmap(QPixmap::fromImage(*palette));
    QColor color(palette->pixel(pointer));
    updateRGB(color.red(), color.green(), color.blue());

    if (ui->radioButton->isChecked()) {
        ++counter;
        ui->previewColor->setStyleSheet(tr("background : rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue()));
    } else {
        if (counter != 0) {
            ui->hSlider->setValue(0);
            ui->hSlider_2->setValue(0);
            ui->hSlider_3->setValue(0);
            counter = 0;
        }
        moveSlider();
    }
}

void MainWindow::updateRGB(int red, int green, int blue)
{
    ui->lineEditRed->setText(tr("%1").arg(red));
    ui->lineEditGreen->setText(tr("%1").arg(green));
    ui->lineEditBlue->setText(tr("%1").arg(blue));

    if (ui->radioButton->isChecked()) {
        ui->hSlider->setValue(red);
        ui->hSlider_2->setValue(green);
        ui->hSlider_3->setValue(blue);
    }
}

void MainWindow::moveSlider()
{
    ui->previewColor->setStyleSheet(tr("background : rgb(%1,%2,%3)").arg(ui->hSlider->value()).arg(ui->hSlider_2->value()).arg(ui->hSlider_3->value()));
    updateRGBSliderMode(ui->hSlider->value(), ui->hSlider_2->value(), ui->hSlider_3->value());
}

void MainWindow::movePoint()
{
    pointer.setX(ui->horizontalSlider->value());
    pointer.setY(ui->verticalSlider->value());
    repaint();
}

void MainWindow::updateRGBSliderMode(int red, int green, int blue)
{
    ui->lineEditRed->setText(tr("%1").arg(red));
    ui->lineEditGreen->setText(tr("%1").arg(green));
    ui->lineEditBlue->setText(tr("%1").arg(blue));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && counter != 0) {
        QPoint position = event->pos();
        QRect rect = ui->labelPalette->geometry();
        if(position.x() <= rect.right() && position.x() >= rect.left()) {
            if(position.y() <= rect.bottom() && position.y() >= rect.top())
            {
                pointer.setX(position.x() - rect.x());
                pointer.setY(position.y() - rect.y());
                pointer.setX(position.x());
                pointer.setY(position.y());
                repaint();
            }
        }
    }
    QWidget::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton && counter != 0) {
        QPoint position = event->pos();
        QRect rect = ui->labelPalette->geometry();
        if(position.x() <= rect.right() && position.x() >= rect.left()) {
            if(position.y() <= rect.bottom() && position.y() >= rect.top())
            {
                pointer.setX(position.x() - rect.x());
                pointer.setY(position.y() - rect.y());
                repaint();
            }
        }
    }
    QWidget::mouseMoveEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}
