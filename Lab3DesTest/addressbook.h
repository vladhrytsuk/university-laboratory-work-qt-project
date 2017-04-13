#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "finddialog.h"

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDataStream>
#include <QTextStream>
#include <QMainWindow>

namespace Ui {
class addressbook;
}

class addressbook : public QMainWindow
{
    Q_OBJECT

public:
    enum Mode {NavigationMode, AddingMode, EditingMode};
    addressbook(QWidget *parent = 0);
    ~addressbook();

public slots:
    void addContact();
    void submitContact();
    void cancel();
    void next();
    void previous();
    void editContact();
    void removeContact();
    void findContact();
    void loadFromFile();
    void saveToFile();
    void exportAsVCard();
    void getContactsCount();

private:
    void updateInterface(Mode mode);
    Mode currentMode;
    finddialog *dialog;

private:
    Ui::addressbook *ui;
    QMap<QString, QString> contacts;
    QString oldName;
    QString oldAddress;
    int contactsCount;
};

#endif // ADDRESSBOOK_H
