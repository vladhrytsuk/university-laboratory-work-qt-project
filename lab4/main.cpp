#include "texteditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icons/icons/new.png"));
    app.setApplicationName("Text Editor");
    app.setApplicationVersion("0.1");
    app.setOrganizationName("Example Soft");
    app.setOrganizationDomain("example.com");

    TextEditor *window = new TextEditor;
    window->show();

    return app.exec();
}
