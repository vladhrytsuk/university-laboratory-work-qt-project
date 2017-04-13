#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openFile()));
}


void Widget::readTextFromFile(QString fileName)
{
    QFile* file = new QFile(fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка открытия для чтения\n";
    }

    QTextStream in(file);
    ui->textEdit->setText(in.readAll());

    file->close();
}

void Widget::openFile()
{
    QFileDialog* fileDialog = new QFileDialog();
    QString fName = fileDialog->getOpenFileName(0, "", "", "*.txt");
    readTextFromFile(fName);
}

Widget::~Widget()
{
    delete ui;
}
