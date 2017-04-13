#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QScrollBar>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void readTextFromFile(QString fileName);

private slots:
    void openFile();

private:
    Ui::Widget *ui;
    QPushButton* pushButton;
    QTextEdit* textEdit;
    QScrollBar* scroll;
};

#endif // WIDGET_H
