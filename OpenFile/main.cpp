#include "fileopen.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileOpen w;
    w.setWindowTitle ("Кол-во букв");
    w.show();
    return a.exec();
}

