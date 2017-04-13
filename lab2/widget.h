#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QPlainTextEdit>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setColor();

private slots:
    void setH(int value);
    void setS(int value);
    void setV(int value);
private:
    Ui::Widget *ui;
    QSpinBox* firstSpinBox;
    QSpinBox* secondSpinBox;
    QSpinBox* thirdSpinBox;
    QSlider* firstSlider;
    QSlider* secondSlider;
    QSlider* thirdSlider;
    QPlainTextEdit* textEdit;
    QLineEdit* lineEdit;
};

#endif // WIDGET_H
