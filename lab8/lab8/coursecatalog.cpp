#include "coursecatalog.h"
#include "ui_coursecatalog.h"

CourseCatalog::CourseCatalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CourseCatalog)
{
    ui->setupUi(this);

    ui->listWidget->addItem("Python for EveryBody");
    ui->listWidget->addItem("Java Programming Introduction");
    ui->listWidget->addItem("Full Stack Web Development");
    ui->listWidget->addItem("Game Desing and Development");
    ui->listWidget->addItem("Web Desing for Everybody");
    ui->listWidget->addItem("Ruby on Rails Web Development");
    ui->listWidget->addItem("HTML, CSS and JavaScript");

    connect(ui->viewDescButton, SIGNAL(clicked()), this, SLOT(accept()));
}

CourseCatalog::~CourseCatalog()
{
    delete ui;
}

void CourseCatalog::on_viewDescButton_clicked()
{
    hide();
}

QString CourseCatalog::getCouseName()
{
    courseName = ui->listWidget->currentItem()->text();
    return courseName;
}
