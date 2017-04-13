#include "texteditor.h"
#include "ui_texteditor.h"

TextEditor::TextEditor(const QString &fileName, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TextEditor)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);

    viewFont.fromString(settings.value("font", QFont("Times", 12)).toString());
    ui->textEdit->setFont(viewFont);

    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);

    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(documentModified()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionCut, SIGNAL(triggered()), ui->textEdit, SLOT(cut()));
    connect(ui->actionCopy, SIGNAL(triggered()), ui->textEdit, SLOT(copy()));
    connect(ui->actionPaste, SIGNAL(triggered()), ui->textEdit, SLOT(paste()));
    connect(ui->actionUndo, SIGNAL(triggered()), ui->textEdit, SLOT(undo()));
    connect(ui->actionRedo, SIGNAL(triggered()), ui->textEdit, SLOT(redo()));
    connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(copyAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(undoAvailable(bool)), ui->actionUndo, SLOT(setEnabled(bool)));
    connect(ui->textEdit, SIGNAL(redoAvailable(bool)), ui->actionRedo, SLOT(setEnabled(bool)));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(saveFileAs()));

    loadFile(fileName);
}

TextEditor::~TextEditor()
{
    delete ui;
}


void TextEditor::on_actionNew_triggered()
{
    TextEditor *newWindow = new TextEditor;
    newWindow->show();
}

void TextEditor::documentModified()
{
    setWindowModified(true);
}

void TextEditor::closeEvent(QCloseEvent *e)
{
    if(isWindowModified())
    {
        switch(QMessageBox::warning(this, tr("Document Modified"), tr("The document has been modified. Do you want to save your changes?\n"
               " You will lose all your changes."), QMessageBox::Yes | QMessageBox::No))
        {
        case QMessageBox::Yes:
            if(saveFile())
            {
                e->accept();
            }
            else
            {
               e->ignore();
            }
            break;

        case QMessageBox::No:
            e->accept();
            break;
        }
    }
    else
    {
        e->accept();
    }
}

bool TextEditor::saveFile()
{
    if(m_fileName.isNull())
    {
        return saveFileAs();
    }
    else
    {
        QFile file(m_fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Error"), tr("File couldn't be opened."), QMessageBox::Ok);
            setFileName(QString());
            return false;
        }
        else
        {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.close();
            this->setWindowModified(false);
            return true;
        }
    }
}

bool TextEditor::saveFileAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save document"), m_fileName.isNull()?
                                                    QDir::currentPath():m_fileName, tr("Text documents (*.txt)"));
    if(fileName.isNull())
    {
        return false;
    }
    else
    {
        setFileName(fileName);
        return saveFile();
    }
}

void TextEditor::replaceText(const QString &text)
{
    const QString sText = searchDialog->getSearchText();

    QString allText = ui->textEdit->toPlainText();

    qDebug() << allText << "\n";

    while (allText.contains(sText)) {
        allText.replace(sText, text);
    }

    qDebug() << allText << "\n";

    ui->textEdit->setText(allText);
}

void TextEditor::setFileName(const QString &str)
{
    m_fileName = str;
    this->setWindowTitle(QString("%1[*] - %2").arg(m_fileName.isNull()?
                         "untitled":QFileInfo(m_fileName).fileName()).arg(QApplication::applicationName()));
}

void TextEditor::on_actionSelectFont_triggered()
{
    bool ok;
    QFont font_init = ui->textEdit->font();
    QFont font = QFontDialog::getFont(&ok, font_init, this);
    if(ok)
    {
        ui->textEdit->setFont(font);
        settings.setValue("Font", font);
    }
}

void TextEditor::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("О программе"), tr("Программа Text Editor, версия 0.1."));
}

void TextEditor::loadFile(const QString &fileName)
{
    if(fileName.isEmpty())
    {
        setFileName(QString());
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Error"), tr("File couldn't be opened."), QMessageBox::Ok);
        setFileName(QString());
        return;
    }
    else
    {
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
        setFileName(fileName);
        this->setWindowModified(false);
    }
}

void TextEditor::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open document"), QDir::currentPath(), tr("Text documents (*.txt)"));
    if(fileName.isNull())
    {
        return;
    }

    if(m_fileName.isNull() && !this->isWindowModified())
    {
        loadFile(fileName);
    }
    else
    {
        TextEditor *newWindow = new TextEditor(fileName);
        newWindow->show();
    }
}

void TextEditor::on_actionSearch_triggered()
{
    searchDialog = new SearchDialog;
    connect(searchDialog, SIGNAL(replace(const QString&)), this, SLOT(replaceText(const QString&)));
    searchDialog->show();
}
