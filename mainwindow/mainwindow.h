#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QTextEdit>
#include <stdlib.h>
#include <QAction>
#include <QKeyEvent>
#include <QTimer>

class TableDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TableDialog(QWidget *parent = 0);

signals:

private slots:
    void makeTable();
    void delta();
    void delta1();
    void delta2();
    void delta3();
    void setToolTip(int, int);

private:
    QPushButton *clickButton;
    QPushButton *Step1;

    QPushButton *Step2;
    QPushButton *Step3;
    QPushButton *Step4;
    QTableWidget *table;
    QTextEdit *textedit;
    QString strs3;
    int a[2][2];
    int b;
    bool tab;
    int c;
    bool step[1];
   QTimer *time=new QTimer(this);
protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
