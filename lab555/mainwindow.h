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
#include<QLineEdit>
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
    QTableView *view, *view1;
    QPushButton *pb, *submitButton, *revert;
    QString tablename, tablename1;
    QSqlTableModel *model, *model1;
    QLineEdit *text, *text1, *text2, *text3, *text4, *select1, *select2;
    QTextEdit *textedit;

};

#endif // MAINWINDOW_H
