#include "colorset.h"
#include "ui_colorset.h"

colorset::colorset(QWidget *parent) : QDialog(parent)
{
        QHBoxLayout *main = new QHBoxLayout;
        QVBoxLayout *color = new QVBoxLayout;
        QVBoxLayout *SpinBox = new QVBoxLayout;
        QVBoxLayout *Slider = new QVBoxLayout;

        QLabel *LabelRed=new QLabel("R");
        QLabel *LabelGreen=new QLabel("G");
        QLabel *LabelBlue=new QLabel("B");
        color->addWidget(LabelRed);
        color->addWidget(LabelGreen);
        color->addWidget(LabelBlue);

        QSlider *SliderRed=new QSlider(Qt::Horizontal);
        QSlider *SliderGreen=new QSlider(Qt::Horizontal);
        QSlider *SliderBlue=new QSlider(Qt::Horizontal);

        SpinBox->addWidget(BoxRed);
        SpinBox->addWidget(BoxGreen);
        SpinBox->addWidget(BoxBlue);
        Slider->addWidget(SliderRed);
        Slider->addWidget(SliderGreen);
        Slider->addWidget(SliderBlue);
        BoxRed->setMinimum(0);
        BoxRed->setMaximum(255);
        BoxGreen->setMinimum(0);
        BoxGreen->setMaximum(255);
        BoxBlue->setMinimum(0);
        BoxBlue->setMaximum(255);
        SliderRed->setMinimum(0);
        SliderRed->setMaximum(255);
        SliderGreen->setMinimum(0);
        SliderGreen->setMaximum(255);
        SliderBlue->setMinimum(0);
        SliderBlue->setMaximum(255);

        text = new QPlainTextEdit;
        text->setEnabled(false);

/*Добавление кнопки, для изменения всех спинов, задание на защиту - НАЧАЛО
        QPushButton *button = new QPushButton("ADD");
        VALUE->setMinimum(0);
        VALUE->setMaximum(255);
        connect(button, SIGNAL(clicked()), this, SLOT(setSpintValue()));*/

        main->addLayout(color);
        main->addLayout(Slider);
        main->addLayout(SpinBox);
        main->addWidget(text);
        //main->addWidget(button);
        //main->addWidget(VALUE);
        setLayout(main);

        connect (BoxRed,SIGNAL(valueChanged(int)),SliderRed,SLOT(setValue(int)));
        connect (SliderRed,SIGNAL(valueChanged(int)),BoxRed,SLOT(setValue(int)));
        connect (BoxGreen,SIGNAL(valueChanged(int)),SliderGreen,SLOT(setValue(int)));
        connect (SliderGreen,SIGNAL(valueChanged(int)),BoxGreen,SLOT(setValue(int)));
        connect (BoxBlue,SIGNAL(valueChanged(int)),SliderBlue,SLOT(setValue(int)));
        connect (SliderBlue,SIGNAL(valueChanged(int)),BoxBlue,SLOT(setValue(int)));

        connect (SliderRed, SIGNAL(sliderMoved(int)), this , SLOT(SetRed(int)));
        connect (SliderGreen, SIGNAL(sliderMoved(int)), this , SLOT(SetGreen(int)));
        connect (SliderBlue, SIGNAL(sliderMoved(int)), this , SLOT(SetBlue(int)));
        connect (BoxRed, SIGNAL(valueChanged(int)), this , SLOT(SetRed(int)));
        connect (BoxGreen, SIGNAL(valueChanged(int)), this , SLOT(SetGreen(int)));
        connect (BoxBlue, SIGNAL(valueChanged(int)), this , SLOT(SetBlue(int)));

}
void colorset::SetRed(int i)
{
        QString str_col;
        r=i;
        str_col+=QString("QPlainTextEdit{background-color:rgb(");
        str_col+=QString::number(r)+QString(",")+QString::number(g)+QString(",")+QString::number(b)+QString(")}");
        setColor(str_col);
}

void colorset::SetGreen(int i){
        QString str_col;
        g=i;
        str_col+=QString("QPlainTextEdit{background-color:rgb(");
        str_col+=QString::number(r)+QString(",")+QString::number(g)+QString(",")+QString::number(b)+QString(")}");
        setColor(str_col);
}

void colorset::SetBlue(int i){
        QString str_col;
        b =i;
        str_col+=QString("QPlainTextEdit{background-color:rgb(");
        str_col+=QString::number(r)+QString(",")+QString::number(g)+QString(",")+QString::number(b)+QString(")}");
        setColor(str_col);
}


void colorset::setColor(QString str_col)
{
        text->setStyleSheet(str_col);
}

/*
void colorset::setSpintValue()
{
    BoxRed->setValue(VALUE->value());
    BoxGreen->setValue(VALUE->value());
    BoxBlue->setValue(VALUE->value());
}
/*Функция для изменения 3-х spinbox - КОНЕЦ*/
