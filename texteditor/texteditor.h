#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QApplication>
#include <QtGui>
#include <QtCore>
#include <QMainWindow>
#include <QTextEdit>
#include <QBoxLayout>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QToolBar>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFontDialog>
#include <QSettings>
#include <QVariant>

#include <QPushButton>


class texteditor : public QMainWindow
{
    Q_OBJECT

public:
    texteditor(const QString fileName = QString(), QWidget *parent = 0);
    ~texteditor();

private:
    QString fileName;
    QTextEdit *text;
    QMenu *MenuFile,*AboutFile, *MenuView,* MenuEdit;
    QToolBar *fileToolBar, *Protect;
    QPushButton *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9;
    QAction *actionNew,*actionClose,*actionExit,*actionOpen,*actionSave,*actionSaveAs,
    *actionCopy,*actionPaste,*actionCut,*actionUndo,*actionRedo,*actionAbout,*actionSelectFont, *actionUpdate;

    void setFileName(const QString &);
    void createActions();
    void createMenues();
    void createToolBar();

    void createButton();
    void createProtect();

private slots:
    void createNew();
    bool save();
    bool saveFileAs();
    void about();
    void open();
    void selectFont();
    void updateText();
    void pushbutton();


};

#endif // TEXTEDITOR_H
