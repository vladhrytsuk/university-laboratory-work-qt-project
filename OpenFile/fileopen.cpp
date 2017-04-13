#include "fileopen.h"
#include "ui_fileopen.h"
#include <QFileDialog>
#include <QFile>
#include <QDebug>

FileOpen::FileOpen()
{
     knopka = new QPushButton("Кол-во букв");
     QVBoxLayout *pole = new QVBoxLayout;
     one = new QLineEdit;
     two = new QLineEdit;
     pole->addWidget(one);
     pole->addWidget(two);
     pole->addWidget(knopka);

     setLayout(pole);
     connect(knopka,SIGNAL(clicked()),this,SLOT(srtlen()));
}

void FileOpen::srtlen()
{
    QString str = one->text();
    int wordCount = str.length();
    QString str2 = QString::number(wordCount);
    two->setText(str2);
}
