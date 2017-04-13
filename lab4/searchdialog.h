#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QWidget>
#include <QString>
#include <QMessageBox>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QWidget
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0);
    QString getSearchText();
    QString getReplaceText();
    ~SearchDialog();

public slots:
    void replaceClicked();

signals:
    void replace(const QString&);

private:
    Ui::SearchDialog *ui;
    QString search_Text;
    QString replace_Text;
};

#endif // SEARCHDIALOG_H
