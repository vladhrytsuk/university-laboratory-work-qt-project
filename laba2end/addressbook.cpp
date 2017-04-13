#include "addressbook.h"
#include "ui_addressbook.h"

addressbook::addressbook(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::addressbook)
{
    ui->setupUi(this);
    contactsCount = 0;

    ui->nameLine->setReadOnly(true);
    ui->addressText->setReadOnly(true);

    dialog = new finddialog;

    ui->addButton->show();
    ui->submitButton->hide();
    ui->cancelButton->hide();
    ui->nextButton->setEnabled(false);
    ui->previousButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->removeButton->setEnabled(false);
    ui->findButton->setEnabled(false);
    ui->loadButton->setToolTip(tr("Load contacts from a file"));
    ui->loadButton->show();
    ui->saveButton->setToolTip(tr("Save contacts to a file"));
    ui->saveButton->setEnabled(false);
    ui->exportButton->setEnabled(false);
    ui->contactsText->setReadOnly(true);

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addContact()));
    connect(ui->submitButton, SIGNAL(clicked()), this, SLOT(submitContact()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->previousButton, SIGNAL(clicked()), this, SLOT(previous()));
    connect(ui->editButton, SIGNAL(clicked()), this, SLOT(editContact()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeContact()));
    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(findContact()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadFromFile()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));
    connect(ui->exportButton, SIGNAL(clicked()), this, SLOT(exportAsVCard()));
    connect(ui->contactsCountButton, SIGNAL(clicked()), this, SLOT(getContactsCount()));

    ui->buttonLayout1->addStretch();

    setWindowTitle(tr("Simple Address Book"));

}

addressbook::~addressbook()
{
    delete ui;
}

void addressbook::updateInterface(Mode mode)
{
    currentMode = mode;

    switch(currentMode)
    {
    case AddingMode:
    case EditingMode:
        ui->nameLine->setReadOnly(false);
        ui->nameLine->setFocus(Qt::OtherFocusReason);
        ui->addressText->setReadOnly(false);

        ui->addButton->setEnabled(false);
        ui->editButton->setEnabled(false);
        ui->removeButton->setEnabled(false);

        ui->nextButton->setEnabled(false);
        ui->previousButton->setEnabled(false);

        ui->submitButton->show();
        ui->cancelButton->show();

        ui->loadButton->setEnabled(false);
        ui->saveButton->setEnabled(false);
        ui->exportButton->setEnabled(false);
        break;
    case NavigationMode:
        if(contacts.isEmpty())
        {
            ui->nameLine->clear();
            ui->addressText->clear();
        }

        ui->nameLine->setReadOnly(true);
        ui->addressText->setReadOnly(true);
        ui->addButton->setEnabled(true);

        int number = contacts.size();
        ui->editButton->setEnabled(number >= 1);
        ui->removeButton->setEnabled(number >= 1);
        ui->findButton->setEnabled(number > 2);
        ui->nextButton->setEnabled(number > 1);
        ui->previousButton->setEnabled(number > 1);

        ui->submitButton->hide();
        ui->cancelButton->hide();

        ui->loadButton->setEnabled(true);
        ui->saveButton->setEnabled(number >= 1);
        ui->exportButton->setEnabled(number >= 1);
        break;
    }
}

void addressbook::addContact()
{
    //contactsCount++;

    oldName = ui->nameLine->text();
    oldAddress = ui->addressText->toPlainText();

    ui->nameLine->clear();
    ui->addressText->clear();

    updateInterface(AddingMode);
}

void addressbook::submitContact()
{
    QString name = ui->nameLine->text();
    QString address = ui->addressText->toPlainText();

    if(name.isEmpty() || address.isEmpty())
    {
        QMessageBox::information(this, tr("Empty Field"), tr("Please enter a name and address."));
        return;
    }

    if(currentMode == AddingMode)
    {
        if(!contacts.contains(name))
        {
            contactsCount++;
            contacts.insert(name, address);
            QMessageBox::information(this, tr("Add Successful"), tr("\"%1\" has been added to your address book.").arg(name));
        }
        else
        {
            QMessageBox::information(this, tr("Add Unsuccessful"), tr("Sorry, \"%1\" is already in your address book.").arg(name));
        }
    }
    else if(currentMode == EditingMode)
    {
        if(oldName != name)
        {
            if(!contacts.contains(name))
            {
                QMessageBox::information(this, tr("Edit Successful"), tr("\"%1\" has been edited in your address book.").arg(oldName));
                contacts.remove(oldName);
                contacts.insert(name, address);
            }
            else
            {
                QMessageBox::information(this, tr("Edit Unsuccessful"), tr("Sorry, \"%1\" is already in your address book.").arg(name));
            }
        }
        else if(oldAddress != address)
        {
            QMessageBox::information(this, tr("Edit Successful"), tr("\"%1\" has been edited in your address book.").arg(name));
            contacts[name] = address;
        }
    }

    updateInterface(NavigationMode);
}

void addressbook::cancel()
{
    ui->nameLine->setText(oldName);
    ui->addressText->setText(oldAddress);

    updateInterface(NavigationMode);
}

void addressbook::next()
{
    QString name = ui->nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if(i != contacts.end())
    {
        i++;
    }

    if(i == contacts.end())
    {
        i = contacts.begin();
    }

    ui->nameLine->setText(i.key());
    ui->addressText->setText(i.value());
}

void addressbook::previous()
{
    QString name = ui->nameLine->text();
    QMap<QString, QString>::iterator i = contacts.find(name);

    if(i == contacts.end())
    {
        ui->nameLine->clear();
        ui->addressText->clear();
        return;
    }

    if(i == contacts.begin())
    {
        i = contacts.end();
    }

    i--;
    ui->nameLine->setText(i.key());
    ui->addressText->setText(i.value());
}

void addressbook::editContact()
{
    oldName = ui->nameLine->text();
    oldAddress = ui->addressText->toPlainText();

    updateInterface(EditingMode);
}

void addressbook::removeContact()
{
    QString name = ui->nameLine->text();
    QString address = ui->addressText->toPlainText();

    if(contacts.contains(name))
    {
        int button = QMessageBox::question(this, tr("Confirm Remove"), tr("Are you sure you want to remove \"%1\"?").arg(name),
                                           QMessageBox::Yes | QMessageBox::No);

        if(button == QMessageBox::Yes)
        {
            contactsCount--;
            previous();
            contacts.remove(name);

            QMessageBox::information(this, tr("Remove Successful"), tr("\"%1\" has been removed from your address book.").arg(name));
        }
    }

    updateInterface(NavigationMode);
}

void addressbook::findContact()
{
    dialog->show();

    if(dialog->exec() == QDialog::Accepted)
    {
        QString contactName = dialog->getFindText();

        if(contacts.contains(contactName))
        {
            ui->nameLine->setText(contactName);
            ui->addressText->setText(contacts.value(contactName));
        }
        else {

            QMessageBox::information(this, tr("Contact Not Found"), tr("Sorry, \"%1\" is not in your address book.").arg(contactName));

            int button = QMessageBox::question(this, tr("Completion of find"), tr("Сontinue find ?"),
                                               QMessageBox::Yes | QMessageBox::No);

            if(button == QMessageBox::Yes) {
                findContact();
            } else {
                return;
            }

        }
    }

    updateInterface(NavigationMode);
}

void addressbook::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Address Book"), "", tr("Address Book (*.abk);;All Files (*)"));

    if(fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);

        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to opne file"), file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_4);
        contacts.empty();
        in >> contacts;

        contactsCount = contacts.size();

        if(contacts.isEmpty())
        {
            QMessageBox::information(this, tr("No contacts in file"), tr("The file you are attempting to open contains no contacts."));
        }
        else
        {
            QMap<QString, QString>::iterator i = contacts.begin();
            ui->nameLine->setText(i.key());
            ui->addressText->setText(i.value());
        }
    }

    updateInterface(NavigationMode);
}

void addressbook::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Address Book"), "", tr("Address Book (*.abk);;All Files (*)"));

    if(fileName.isEmpty())
    {
        return;
    }
    else
    {
        QFile file(fileName);

        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_4);
        out << contacts;
    }
}

void addressbook::exportAsVCard()
{
    QString name = ui->nameLine->text();
    QString address = ui->addressText->toPlainText();
    QString firstName;
    QString lastName;
    QStringList nameList;

    int index = name.indexOf(" ");

    if(index != -1)
    {
        nameList = name.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        firstName = nameList.first();
        lastName = nameList.last();
    }
    else
    {
        firstName = name;
        lastName = "";
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Contact"), "", tr("vCard Files (*.vcf);;All Files (*)"));

    if(fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QTextStream out(&file);

    out << "BEGIN:VCARD" << "\n";
    out << "VERSION:2.1" << "\n";
    out << "N:" << lastName << ";" << firstName << "\n";

    if(!nameList.isEmpty())
    {
        out << "FN:" << nameList.join(" ") << "\n";
    }
    else
    {
        out << "FN:" << firstName << "\n";
    }

    address.replace(";", "\\;", Qt::CaseInsensitive);
    address.replace("\n", ";", Qt::CaseInsensitive);
    address.replace(",", " ", Qt::CaseInsensitive);

    out << "ADR;HOME:;" << address << "\n";
    out << "END:VCARD" << "\n";

    QMessageBox::information(this, tr("Export Successful"), tr("\"%1\" has been exported as a vCard.").arg(name));
}

void addressbook::getContactsCount()
{
    QString temp = "";
    temp.setNum(contactsCount);
    ui->contactsText->setText(temp);
}

