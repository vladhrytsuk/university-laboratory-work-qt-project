#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle ("ЗАЩИТА");
    w.setFixedHeight(280);
    w.setFixedWidth(310);
    w.show();
    return a.exec();
}

