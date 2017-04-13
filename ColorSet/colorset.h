#ifndef COLORSET_H
#define COLORSET_H
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QPlainTextEdit>
#include <QWidget>
#include <QHBoxLayout>
#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>

class colorset : public QDialog
{
    Q_OBJECT
public:
    explicit colorset(QWidget *parent = 0);

private:
    int r = 0,g = 0,b = 0;
    QHBoxLayout *Main,*Color,SpinBox, *Slider,*ma;
    QLabel *LabelRed,*LabelGreen,*LabelBlue;
    QSpinBox *BoxRed= new QSpinBox;
    QSpinBox *BoxGreen = new QSpinBox;
    QSpinBox *BoxBlue= new QSpinBox;
    QSlider *SliderRed,*SliderGreen,*SliderBlue;
    QPlainTextEdit *text;
    QSpinBox *VALUE = new QSpinBox;
    void setColor(QString);

protected slots:
    void SetRed(int);
    void SetGreen(int);
    void SetBlue(int);
  //  void setSpintValue();
};
#endif

