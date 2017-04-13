#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QColor>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->firstSpinBox->setRange(0, 360);
    ui->secondSpinBox->setRange(0, 100);
    ui->thirdSpinBox->setRange(0, 100);
    ui->firstSlider->setRange(0, 360);
    ui->secondSlider->setRange(0, 100);
    ui->thirdSlider->setRange(0, 100);
    ui->textEdit->setEnabled(false);

    connect(ui->firstSpinBox, SIGNAL(valueChanged(int)), this, SLOT(seH(int)));
    connect(ui->firstSlider, SIGNAL(valueChanged(int)), this, SLOT(setH(int)));
    connect(ui->secondSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setS(int)));
    connect(ui->secondSlider, SIGNAL(valueChanged(int)), this, SLOT(setS(int)));
    connect(ui->thirdSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setV(int)));
    connect(ui->thirdSlider, SIGNAL(valueChanged(int)), this, SLOT(setV(int)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setColor()
{
    QString str = "backGround : rgb(";
    QString temp;

    double r, g, b;

    int h = ui->firstSpinBox->value();
    int s = ui->secondSpinBox->value();
    int v = ui->thirdSpinBox->value();

   // QColor* color = new QColor;
  //  color->setHsv(h, s, v);



    unsigned char region, remainder, p, q, t;


    if (s == 0)
    {
        r = v;
        g = v;
        b = v;
    }

    region = h / 43;
    remainder = (h - (region * 43)) * 6;

    p = (v * (255 - s)) >> 8;
    q = (v * (255 - ((s * remainder) >> 8))) >> 8;
    t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
    case 0:
        r = v; g = t; b = p;
        break;
    case 1:
        r = q; g = v; b = p;
        break;
    case 2:
        r = p; g = v; b = t;
        break;
    case 3:
        r = p; g = q; b = v;
        break;
    case 4:
        r = t; g = p; b = v;
        break;
    default:
        r = v; g = p; b = q;
        break;
    }


    qDebug() << r << " " << g << " " << b;

    temp.setNum(r);
    str += temp + ',';
    temp.setNum(g);
    str += temp + ',';
    temp.setNum(b);
    str += temp +')';
    ui->textEdit->setStyleSheet(str);

    //QColor* color = new QColor(ui->firstSpinBox->value(), ui->secondSpinBox->value(), ui->thirdSpinBox->value());
    //color->HexRgb;
    //ui->lineEdit->setText(color->name());
}

void Widget::setH(int value)
{
    connect(ui->firstSpinBox, SIGNAL(valueChanged(int)), ui->firstSlider, SLOT(setValue(int)));
    connect(ui->firstSlider, SIGNAL(valueChanged(int)), ui->firstSpinBox, SLOT(setValue(int)));
    setColor();
}

void Widget::setS(int value)
{
    connect(ui->secondSpinBox, SIGNAL(valueChanged(int)), ui->secondSlider, SLOT(setValue(int)));
    connect(ui->secondSlider, SIGNAL(valueChanged(int)), ui->secondSpinBox, SLOT(setValue(int)));
    setColor();
}

void Widget::setV(int value)
{
    connect(ui->thirdSpinBox, SIGNAL(valueChanged(int)), ui->thirdSlider, SLOT(setValue(int)));
    connect(ui->thirdSlider, SIGNAL(valueChanged(int)), ui->thirdSpinBox, SLOT(setValue(int)));
    setColor();
}


