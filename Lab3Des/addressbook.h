#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "finddialog.h"

#include <QMainWindow>
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

class AddressBook : public QWidget
{
    Q_OBJECT

public:
    enum Mode {NavigationMode, AddingMode, EditingMode};
    AddressBook(QWidget *parent = 0);
    ~AddressBook();

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
    QLineEdit *nameLine;
    QTextEdit *addressText;
    QLineEdit *contactsText;
    QPushButton *addButton;
    QPushButton *contactsCountButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *findButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *exportButton;
    Mode currentMode;
    FindDialog *dialog;

private:
    QMap<QString, QString> contacts;
    QString oldName;
    QString oldAddress;
    int contactsCount;
};

#endif // ADDRESSBOOK_H
