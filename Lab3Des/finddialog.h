#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);
    QString getFindText();
    ~FindDialog();

public slots:
    void findClicked();

private:
    QString findText;
    QLineEdit *lineEdit;
    QPushButton *findButton;
};

#endif // FINDDIALOG_H
