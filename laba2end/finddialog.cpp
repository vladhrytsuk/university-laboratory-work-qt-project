#include "finddialog.h"

finddialog::finddialog(QWidget *parent) : QDialog(parent)
{
    QLabel *findLabel = new QLabel(tr("Enter the name of a contact:"));
    lineEdit = new QLineEdit;

    findButton = new QPushButton(tr("&Find"));

    findText = "";

    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(accept()));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(findLabel);
    layout->addWidget(lineEdit);
    layout->addWidget(findButton);

    setLayout(layout);
    setWindowTitle(tr("Find a Contact"));
}

finddialog::~finddialog()
{
}

QString finddialog::getFindText()
{
    return findText;
}

void finddialog::findClicked()
{
    QString text = lineEdit->text();

    if(text.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"), tr("Please enter a name."));
        return;
    }
    else
    {
        findText = text;
        lineEdit->clear();
        hide();
    }
}
