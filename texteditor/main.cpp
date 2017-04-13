#include "texteditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    texteditor w;
    a.setWindowIcon(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/new_file.png"));
    w.setWindowTitle("Text Editor");
    w.resize(600,600);
    w.show();
    return a.exec();
}
