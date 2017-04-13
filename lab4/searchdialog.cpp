#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(replaceClicked()));
}

void SearchDialog::replaceClicked()
{
    QString sText = ui->lineEdit->text();
    search_Text = sText;
    emit replace(ui->lineEdit_2->text());
    this->close();
}

QString SearchDialog::getSearchText()
{
    return search_Text;
}

QString SearchDialog::getReplaceText()
{
    return replace_Text;
}

SearchDialog::~SearchDialog()
{
    delete ui;
}
