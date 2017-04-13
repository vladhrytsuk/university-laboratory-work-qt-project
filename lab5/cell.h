#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include <QString>

class Cell : public QLabel
{
    Q_OBJECT
public:
    Cell(QWidget *parent = 0);
    void enterEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void setPos(int x, int y);
    const int getX();
    const int getY();
    ~Cell();

signals:
    void clicked(const QString&);

private:
    int x;
    int y;
};

#endif // CELL_H
