#include <QApplication>
#include "address.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    address a;
    a.show();

    return app.exec();
}
