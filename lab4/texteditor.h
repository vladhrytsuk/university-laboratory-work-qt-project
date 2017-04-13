#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <QSettings>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QFileDialog>

#include <QDebug>

#include "searchdialog.h"

namespace Ui {
class TextEditor;
}

class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextEditor(const QString &fileName = QString(), QWidget *parent = 0);
    ~TextEditor();

private slots:
    void on_actionNew_triggered();
    void on_actionSelectFont_triggered();
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void documentModified();
    bool saveFile();
    bool saveFileAs();
    void replaceText(const QString&);

    void on_actionSearch_triggered();

protected:
    void closeEvent(QCloseEvent *e);

private:
    Ui::TextEditor *ui;
    QString m_fileName;
    QSettings settings;
    QFont viewFont;
    void loadFile(const QString &fileName);
    void setFileName(const QString &str);

    SearchDialog *searchDialog;

};

#endif // TEXTEDITOR_H
