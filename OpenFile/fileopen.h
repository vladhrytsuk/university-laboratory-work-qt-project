#ifndef FILEOPEN_H
#define FILEOPEN_H
#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

class FileOpen: public QWidget {
    Q_OBJECT
public:
    FileOpen();
    QLineEdit *one, *two;
private:
    QPushButton *knopka;
protected slots:
    void srtlen();
};

#endif // FILEOPEN_H
