#include "fifteen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(QApplication::tr("QWidget {background-color: red; font-family: Times; font-weight: bold;}"
                                       "QMenu {border: 2px solid black;}"
                                       "QMenuBar::item {background-color: red;}"));
    Fifteen w;
    w.show();

    return a.exec();
}
