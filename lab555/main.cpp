#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("C:/Users/Greed/Desktop/Qt - Project/lab5/mydatabase.sqlite");
    if (!dbase.open()) {
        qDebug() << "Ошибка соединения.";

    }
    TableDialog w("fio","vid");
    w.resize(1200,600);
    w.show();

    return a.exec();
}
