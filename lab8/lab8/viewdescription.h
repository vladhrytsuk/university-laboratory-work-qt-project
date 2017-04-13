#ifndef VIEWDESCRIPTION_H
#define VIEWDESCRIPTION_H

#include <QDialog>
#include <QFile>
#include <QIODevice>

namespace Ui {
class ViewDescription;
}

class ViewDescription : public QDialog
{
    Q_OBJECT

public:
    explicit ViewDescription(QWidget *parent = 0);
    ~ViewDescription();

private slots:
    void on_signButton_clicked();

public slots:
    void setCourseDescription();
    void setFileName(QString fName);

private:
    Ui::ViewDescription *ui;
    QString fileName;
};

#endif // VIEWDESCRIPTION_H
