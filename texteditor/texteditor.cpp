#include "texteditor.h"

texteditor::texteditor(QString fileName, QWidget *parent) : QMainWindow(parent)
{
    text = new QTextEdit(this);
    setCentralWidget(text);
    createActions();
    createToolBar();
    createMenues();

    createButton();
    createProtect();

}

texteditor::~texteditor()
{
}

void texteditor::createButton(){
    button1 = new QPushButton;
    button1->setIcon(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/editText.png"));
    button1->setAutoDefault(true);

    button2 = new QPushButton;
    button2->setIcon(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/editText.png"));
    button2->setAutoDefault(true);

    button3 = new QPushButton;
    button3->setIcon(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/editText.png"));
    button3->setAutoDefault(true);

    button4 = new QPushButton;
    button4->setIcon(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/editText.png"));
    button4->setAutoDefault(true);

    button5 = new QPushButton;
    button5->setIcon(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/editText.png"));
    button5->setAutoDefault(true);

    button6 = new QPushButton;
    button6->setIcon(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/editText.png"));
    button6->setAutoDefault(true);

    button7 = new QPushButton;
    button7->setIcon(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/editText.png"));
    button7->setAutoDefault(true);

    button8 = new QPushButton;
    button8->setIcon(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/editText.png"));
    button8->setAutoDefault(true);

    button9 = new QPushButton;
    button9->setIcon(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/editText.png"));
    button9->setAutoDefault(true);

    connect(button2, SIGNAL (clicked()),button1, SLOT (pushbutton()));
}

void texteditor::pushbutton(){
    button1->setAutoDefault(false);
    button2->setAutoDefault(true);
}

void texteditor::createProtect(){
    Protect = new QToolBar(tr("Protect"), this);
    addToolBar(Protect);
    Protect->addWidget(button1);
    Protect->addWidget(button2);
   // Protect->addWidget(button3);
    //Protect->addWidget(button4);
    Protect->addWidget(button5);
    Protect->addWidget(button6);
    Protect->addWidget(button7);
    Protect->addWidget(button8);
    Protect->addWidget(button9);
}

void texteditor::createActions(){

    actionOpen = new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/open.png"),tr("Открыть"),this);
    actionOpen->setStatusTip(tr("Открыть файл"));
    actionOpen->setShortcut(QKeySequence("ctrl+o"));

    actionNew = new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/new_file.png"),tr("Создать"),this);
    actionNew->setStatusTip(tr("Создать новый документ"));
    actionNew->setShortcut(QKeySequence("ctrl+n"));


    actionClose = new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/close.png"),tr("Закрыть"),this);
    actionClose->setStatusTip(tr("Закрыть текущее окно"));
    actionClose->setShortcut(QKeySequence("ctrl+w"));

    actionExit = new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/exit.png"),tr("Выход"),this);
    actionExit->setStatusTip(tr("Закрыть приложение"));
    actionExit->setShortcut(QKeySequence("ALT + F4"));

    actionSave=new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/save.png"),tr("Сохранить"),this);
    actionSave->setShortcut(QKeySequence("ctrl+s"));
    actionSaveAs = new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/save_as.png"),tr("Сохранить как"), this);
    actionSaveAs->setShortcut(QKeySequence("ctrl+shift+s"));

    actionAbout = new QAction(tr("О программе"), this);
    actionCopy=new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/copy.png"),tr("Копировать"),this);
    actionPaste=new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/paste.png"),tr("Вставить"),this);
    actionCut=new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/cut.png"),tr("Вырезать"),this);
    actionUndo=new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/undo.png"),tr("Отменить"),this);
    actionRedo=new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/redo.png"),tr("Повторить"),this);
    actionUpdate = new QAction(QIcon("C:/Users/Greed/Desktop/Qt - Project/texteditor/icon/editText.png"),tr("ЗАЩИТА"),this);
    actionSelectFont = new QAction(tr("Изменить шрифт"), this);

    actionCopy->setEnabled(false);
    actionCut->setEnabled(false);

    connect(actionCopy, SIGNAL(triggered(bool)), this->text, SLOT(copy()));
    connect(actionPaste, SIGNAL(triggered(bool)), this->text, SLOT(paste()));
    connect(actionCut, SIGNAL(triggered(bool)), this->text, SLOT(cut()));
    connect(actionUndo, SIGNAL(triggered(bool)), this->text, SLOT(undo()));
    connect(actionRedo, SIGNAL(triggered(bool)), this->text, SLOT(redo()));


    connect(actionSave, SIGNAL(triggered(bool)), this, SLOT(save()) );
    connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(open()) );
    connect(actionNew, SIGNAL(triggered(bool)), this, SLOT(createNew()) );
    connect(actionClose, SIGNAL(triggered(bool)), this, SLOT(close()) );
    connect(actionExit, SIGNAL(triggered(bool)), qApp, SLOT(closeAllWindows()) );
    connect(actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(saveFileAs()) );
    connect(actionSelectFont, SIGNAL(triggered(bool)), this, SLOT(selectFont()));
    connect(actionAbout, SIGNAL(triggered(bool)), this, SLOT(about()));

    connect(actionUpdate, SIGNAL(triggered(bool)), this, SLOT(updateText())); // защита 3-й лабы

    connect(text,SIGNAL(copyAvailable(bool)),actionCopy,SLOT(setEnabled(bool)));
    connect(text,SIGNAL(copyAvailable(bool)),actionCut,SLOT(setEnabled(bool)));


}

void texteditor::createToolBar(){

    fileToolBar = new QToolBar(tr("File"),this);
    addToolBar(fileToolBar);
    fileToolBar->addAction(actionNew);
    fileToolBar->addAction(actionOpen);
    fileToolBar->addAction(actionSave);
    fileToolBar->addAction(actionCopy);
    fileToolBar->addAction(actionPaste);
    fileToolBar->addAction(actionCut);
    fileToolBar->addAction(actionUndo);
    fileToolBar->addAction(actionRedo);
    fileToolBar->addAction(actionUpdate);

}

void texteditor::createMenues(){

    MenuFile = menuBar()->addMenu(tr("Файл"));
    MenuEdit = menuBar()->addMenu(tr("Редактировать"));
    MenuView = menuBar()->addMenu(tr("Вид"));
    AboutFile = menuBar()->addMenu(tr("Справка"));

    AboutFile->addAction(actionAbout);

    MenuFile->addAction(actionNew);
    MenuFile->addAction(actionOpen);
    MenuFile->addSeparator();
    MenuFile->addAction(actionSave);
    MenuFile->addAction(actionSaveAs);
    MenuFile->addAction(actionExit);
    MenuFile->addAction(actionClose);

    MenuEdit->addAction(actionCopy);
    MenuEdit->addAction(actionCut);
    MenuEdit->addAction(actionPaste);
    MenuEdit->addAction(actionUndo);
    MenuEdit->addAction(actionRedo);

    MenuView->addAction(actionSelectFont);


}
void texteditor::createNew(){
        texteditor *window = new texteditor(QString(), this);
        window->show();
        window->setWindowTitle("Новое окно[*]");
        window->resize(600,600);
}


void texteditor::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "",tr("TXT files (*.txt);;All Files (*)"));

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Ошибка"), tr("Нельзя открыть файл"));
                return;
            }
            QTextStream in(&file);
            text->setText(in.readAll());
            file.close();
        }
}

bool texteditor::save()
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        return saveFileAs();
    }   else {
                QTextStream stream(&file);
                stream << text->toPlainText();
                file.close();
             }
    file.close();

}
bool texteditor::saveFileAs()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить как..."), QString(), tr("TXT files (*.txt);;All Files (*)"));
    if (filename.isNull())
        return false;
    else
    {
        setFileName(filename);
        return save();
    }

}

void texteditor::setFileName(const QString &name)
{
    fileName = name;
    this->setWindowTitle(QString("%1[*] - %2")
                         .arg(fileName.isNull()?"untitled":QFileInfo(fileName).fileName())
                         .arg(QApplication::applicationName()));
}
void texteditor::about()
{
    QMessageBox::aboutQt(this);
}
void texteditor::selectFont(){
    bool ok;
    QFont FONT = QFontDialog::getFont(&ok, QFont("Times New Roman", 12), this);

    if(ok){
        text->setFont(FONT);
    }
}

void texteditor::updateText() // защита 3-й лабы
{
   QString str;
   str = text->toPlainText();
   str.replace("а", "А");
   str.replace("е", "Е");
   str.replace("ё", "Ё");
   str.replace("и", "И");
   str.replace("о", "О");
   str.replace("у", "У");
   str.replace("ы", "Ы");
   str.replace("э", "Э");
   str.replace("ю", "Ю");
   str.replace("я", "Я");
  text->setText(str);
}
