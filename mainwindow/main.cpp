#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
  QApplication app( argc, argv );

  TableDialog dlg;
  dlg.resize(700,400);
  dlg.show();
  return app.exec();
}
