#include "viewdescription.h"
#include "ui_viewdescription.h"

ViewDescription::ViewDescription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDescription)
{
    ui->setupUi(this);

    connect(ui->signButton, SIGNAL(clicked()), this, SLOT(accept()));
}

ViewDescription::~ViewDescription()
{
    delete ui;
}

void ViewDescription::on_signButton_clicked()
{
    hide();
}

void ViewDescription::setCourseDescription()
{
    QFile file(fileName);
    QString courseDescription = "", temp = "";
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            temp = file.readLine();
            courseDescription += temp;
        }
    } else {
        courseDescription = tr("Курс ещё не записан");
    }

    ui->textEdit->setText(courseDescription);
}

void ViewDescription::setFileName(QString fName)
{
    fileName = "C:/Users/SergeiPC/Documents/Qt/lab8/lab8/" + fName + ".txt";
}
