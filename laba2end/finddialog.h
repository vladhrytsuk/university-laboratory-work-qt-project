#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

class finddialog : public QDialog
{
    Q_OBJECT

public:
    finddialog(QWidget *parent = 0);
    QString getFindText();
    ~finddialog();

public slots:
    void findClicked();

private:
    QString findText;
    QLineEdit *lineEdit;
    QPushButton *findButton;
};

#endif // FINDDIALOG_H
