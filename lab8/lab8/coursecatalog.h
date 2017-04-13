#ifndef COURSECATALOG_H
#define COURSECATALOG_H

#include <QDialog>

namespace Ui {
class CourseCatalog;
}

class CourseCatalog : public QDialog
{
    Q_OBJECT

public:
    explicit CourseCatalog(QWidget *parent = 0);
    QString getCouseName();
    ~CourseCatalog();

private slots:
    void on_viewDescButton_clicked();

private:
    Ui::CourseCatalog *ui;
    QString courseName;
};

#endif // COURSECATALOG_H
