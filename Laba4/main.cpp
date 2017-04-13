#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("D:/eclipse/workspace/qt/untitled3/mydatabase.sqlite");
    if (!dbase.open()) {
        qDebug() << "Что-то не так с соединением!";

    }

    TableDialog w("fio","vid");
    w.resize(1400,600);
    w.show();

    return a.exec();
}
