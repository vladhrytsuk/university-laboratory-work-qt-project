#include <QApplication>
#include "colorset.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    colorset w;
    w.setWindowTitle("Color");
    w.show();
    return a.exec();
}
