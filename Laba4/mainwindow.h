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
#include <QLineEdit>
#include <QtSql>
class TableDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TableDialog(const QString &tableName,const QString &tableName1,QWidget *parent = 0);

signals:

private slots:
    void addRow();
    void addRow1();
    void submit();
    void addData();
    void sel();
    void sel1();

private:
    QTableView *view;
    QTableView *view1;
    QPushButton *pb;
    QPushButton *submitButton;
    QPushButton *revert;
    QString tablename;
    QString tablename1;
    QSqlTableModel *model;
    QSqlTableModel *model1;
    QLineEdit *text;
    QLineEdit *text1;
    QLineEdit *text2;
    QLineEdit *text3;
    QLineEdit *text4;
    QTextEdit *textedit;
    QLineEdit *select1;
    QLineEdit *select2;

};

#endif // MAINWINDOW_H
