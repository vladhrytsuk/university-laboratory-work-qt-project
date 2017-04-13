#include "cell.h"

Cell::Cell(QWidget *parent) : QLabel(parent)
{
    x = y = -1;
    setFont(QFont(tr("Times"), 20, QFont::Bold));
    setAlignment(Qt::AlignCenter);
    setMinimumSize(100, 100);
    setStyleSheet(tr("QLabel {border: 2px solid white; border-radius: 5px; background-color: red;}"
                     "QLabel:hover {background-color: white;}"));
}

void Cell::enterEvent(QEvent *event)
{
    QLabel::enterEvent(event);
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    QString temp = this->text();
    emit clicked(temp);
    QLabel::mousePressEvent(event);
}

void Cell::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

const int Cell::getX()
{
    return x;
}

const int Cell::getY()
{
    return y;
}

Cell::~Cell()
{

}
