#include "fifteen.h"

Fifteen::Fifteen(QWidget *parent): QDialog(parent) {
    QSettings *statistic = new QSettings("Statistic.conf", QSettings::NativeFormat);
    game = statistic->value("Game").toInt();
    win = statistic->value("Win").toInt();
    cellsLayout = new QGridLayout;
    for (int x = 0; x < 4; x++) {
        for(int y = 0; y < 4; y++) {
            if(x == 3 && y == 3) {
                break;
            }
            Cell *lbl = new Cell;
            lbl->setText(tr("%1").arg(4 * x + y + 1));
            lbl->setToolTip(tr("%1").arg(4 * x + y + 1));
            lbl->setPos(x, y);
            connect(lbl, SIGNAL(clicked(const QString&)), this, SLOT(cellPressed()));
            cellsLayout->addWidget(lbl, x, y);
        }
    }

    menuBar = new QMenuBar;
    createActions();
    createMenu();

    QHBoxLayout *menuBarLayout = new QHBoxLayout;
    menuBarLayout->addWidget(menuBar);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(menuBarLayout);
    mainLayout->addLayout(cellsLayout);
    setLayout(mainLayout);
    setFixedSize(sizeHint());
    setWindowTitle(tr("Пятнашки"));
}

void Fifteen::cellPressed() {
    int x = -1, y = -1;
    findEmptyCell(x, y);
    if((x == -1) || (y == -1)) {
        QMessageBox::warning(this, "Error", "No empty cell.");
        return;
    }
    Cell *cell = (Cell*)sender();
    int index = cellsLayout->indexOf(cell);

    int xCell, yCell, rSpan, cSpan;
    cellsLayout->getItemPosition(index, &xCell, &yCell, &rSpan, &cSpan);
    if(xCell == x) {
        if(yCell == y - 1 || yCell == y + 1) {
            cellsLayout->takeAt(index);
            cellsLayout->addWidget(cell, x, y);
            if(isWin()) {
                winMessage();
            }
        }
    }
    if(yCell == y) {
        if(xCell == x - 1 || xCell == x + 1) {
            cellsLayout->takeAt(index);
            cellsLayout->addWidget(cell, x, y);
            if(isWin()) {
                winMessage();
            }
        }
    }
}

void Fifteen::findEmptyCell(int &x, int &y) {
    bool flag = false;
    for (x = 0; !flag && x < 4; ++x) {
        for (y = 0; y < 4; ++y) {
            QLayoutItem *item;
            item = cellsLayout->itemAtPosition(x, y);
            if(item == 0) {
                flag = true;
                break;
            }
        }
    }
    x -= 1;
    if(!flag) {
        x = y = -1;
    }
}

bool Fifteen::isWin() {
    int x, y;
    findEmptyCell(x, y);
    if(x != 3 || y != 3) {
        return false;
    }
    for (int q = 0; q < 15; ++q) {
        int rSpan, cSpan;
        Cell *cell = (Cell*)(cellsLayout->itemAt(q)->widget());
        cellsLayout->getItemPosition(q, &x, &y, &rSpan, &cSpan);
        if(x != cell->getX() || y != cell->getY()) {
            return false;
        }
    }
    return true;
}

void Fifteen::winMessage() {
    ++win;
    saveStatistic();
    QMessageBox::information(this, "Triumph", "You won the game!");
}

void Fifteen::saveStatistic() {
    QSettings *statistic = new QSettings("Statistic.conf", QSettings::NativeFormat);
    statistic->setValue("Game", game);
    statistic->setValue("Win", win);
    statistic->sync();
}

void Fifteen::mix() {
    ++game;
    saveStatistic();
    for(int i = 0; i < 10; i++) {
        for(int k = 0; k < 15; k++) {
            int rSpan, cSpan;
            Cell *cell1 = (Cell*)(cellsLayout->itemAt(k)->widget());
            int x1, x2, y1, y2;
            cellsLayout->getItemPosition(k, &x1, &y1, &rSpan, &cSpan);
            int newPos = qrand() % 15;
            Cell *cell2 = (Cell*)(cellsLayout->itemAt(newPos)->widget());
            cellsLayout->getItemPosition(newPos, &x2, &y2, &rSpan, &cSpan);
            cellsLayout->removeWidget(cell1);
            cellsLayout->removeWidget(cell2);
            cellsLayout->addWidget(cell1, x2, y2);
            cellsLayout->addWidget(cell2, x1, y1);
        }
    }
}

void Fifteen::statistic() {
    QString str = QString("Games: %1\nNumber of wins: %2").arg(game).arg(win);
    QMessageBox::information(this, "Statistic", str);
}

void Fifteen::createActions() {
    newGameAction = new QAction(tr("&New game"), this);
    newGameAction->setShortcut(QKeySequence::New);
    connect(newGameAction, SIGNAL(triggered()), this, SLOT(mix()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    loadImageAction = new QAction(tr("&Load image"), this);
    loadImageAction->setShortcut(QKeySequence("Ctrl+L"));
    connect(loadImageAction, SIGNAL(triggered()), this, SLOT(loadImage()));

    assembleAction = new QAction(tr("&Assemble"), this);
    assembleAction->setShortcut(QKeySequence("Ctrl+A"));
    connect(assembleAction, SIGNAL(triggered()), this, SLOT(assemble()));

    setNumberAction = new QAction(tr("Set Nu&merical"), this);
    setNumberAction->setShortcut(QKeySequence("Ctrl+M"));
    connect(setNumberAction, SIGNAL(triggered()), this, SLOT(setNumber()));

    statisticAction = new QAction(tr("Statistic"), this);
    connect(statisticAction, SIGNAL(triggered()), this, SLOT(statistic()));

    /*4 Лабораторна работа*/
    level3x3 = new QAction(tr("level 3x3"), this);
    connect(level3x3, SIGNAL(triggered()), this, SLOT(level3()));

    level4x4 = new QAction(tr("level 4x4"), this);
    connect(level4x4, SIGNAL(triggered()), this, SLOT(level4()));

    level5x5 = new QAction(tr("level 5x5"), this);
    connect(level5x5, SIGNAL(triggered()), this, SLOT(level5()));

    //add
    cellCount = new QAction(tr("MyFunction"), this);
    connect(cellCount, SIGNAL(triggered()), this, SLOT(myFunction()));

    setDefaultBackgroundAction = new QAction(tr("&Default"), this);
    connect(setDefaultBackgroundAction, SIGNAL(triggered()), this, SLOT(setDefaultBackground()));

    setBackgroundFromImageAction = new QAction(tr("From image"), this);
    connect(setBackgroundFromImageAction, SIGNAL(triggered()), this, SLOT(setBackgroundFromImage()));
}

/*Лабораторная работа 4 - START*/

void Fifteen::level3() {
//    int x, y, rSpan, cSpan;
//    for (int i = 0; i < 15; ++i) {
//        Cell *cell = (Cell*)(cellsLayout->itemAt(i)->widget());
//        cellsLayout->getItemPosition(i, &x, &y, &rSpan, &cSpan);

//        cellsLayout->removeWidget(cell);
//    }

    for(int k = 0; k < 15; k++) {
        int rSpan, cSpan;
        Cell *cell1 = (Cell*)(cellsLayout->itemAt(k)->widget());
        int x1, x2, y1, y2;
        cellsLayout->getItemPosition(k, &x1, &y1, &rSpan, &cSpan);
        int newPos = qrand() % 15;
        Cell *cell2 = (Cell*)(cellsLayout->itemAt(newPos)->widget());
        cellsLayout->getItemPosition(newPos, &x2, &y2, &rSpan, &cSpan);
        cellsLayout->removeWidget(cell1);
        cellsLayout->removeWidget(cell2);
    }

//    for (int x = 0; x < 3; x++) {
//        for(int y = 0; y < 3; y++) {
//            if(x == 2 && y == 2) {
//                break;
//            }
//            Cell *lbl = new Cell;
//            lbl->setText(tr("%1").arg(3 * x + y + 1));
//            lbl->setToolTip(tr("%1").arg(3 * x + y + 1));
//            lbl->setPos(x, y);
//            connect(lbl, SIGNAL(clicked(const QString&)), this, SLOT(cellPressed()));
//            cellsLayout->addWidget(lbl, x, y);
//        }
//    }
//    setFixedSize(sizeHint());
}

void Fifteen::level4() {
    for (int x = 0; x < 4; x++) {
        for(int y = 0; y < 4; y++) {
            if(x == 3 && y == 3) {
                break;
            }
            Cell *lbl = new Cell;
            lbl->setText(tr("%1").arg(4 * x + y + 1));
            lbl->setToolTip(tr("%1").arg(4 * x + y + 1));
            lbl->setPos(x, y);
            connect(lbl, SIGNAL(clicked(const QString&)), this, SLOT(cellPressed()));
            cellsLayout->addWidget(lbl, x, y);
        }
    }
    setFixedSize(sizeHint());
}

void Fifteen::level5() {
    for (int x = 0; x < 5; x++) {
        for(int y = 0; y < 5; y++) {
            if(x == 4 && y == 4) {
                break;
            }
            Cell *lbl = new Cell;
            lbl->setText(tr("%1").arg(5 * x + y + 1));
            lbl->setToolTip(tr("%1").arg(5 * x + y + 1));
            lbl->setPos(x, y);
            connect(lbl, SIGNAL(clicked(const QString&)), this, SLOT(cellPressed()));
            cellsLayout->addWidget(lbl, x, y);
        }
    }
    setFixedSize(sizeHint());
}

/*Лабораторная работа 4 - END*/

//add
void Fifteen::myFunction() {
    int count = 0;
    int x, y, rSpan, cSpan;
    for (int i = 0; i < 15; ++i) {
        Cell *cell = (Cell*)(cellsLayout->itemAt(i)->widget());
        cellsLayout->getItemPosition(i, &x, &y, &rSpan, &cSpan);
        if (x != cell->getX() || y != cell->getY()) {
            count++;
        }
    }
    QString temp = "";
    temp.setNum(count);
    QMessageBox::information(this, "Information", temp);
}

void Fifteen::createMenu() {
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newGameAction);
    fileMenu->addAction(assembleAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    viewMenu = menuBar->addMenu(tr("&Edit"));
    viewMenu->addAction(setNumberAction);
    viewMenu->addAction(loadImageAction);
    setBackgroundMenu = viewMenu->addMenu(tr("Set background"));
    setBackgroundMenu->addAction(setDefaultBackgroundAction);
    setBackgroundMenu->addAction(setBackgroundFromImageAction);

    helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(statisticAction);
    //add
    helpMenu->addAction(cellCount);

    gameLevel = menuBar->addMenu(tr("&Level"));
    gameLevel->addAction(level3x3);
    gameLevel->addAction(level4x4);
    gameLevel->addAction(level5x5);
}

void Fifteen::keyPressEvent(QKeyEvent *event) {
    int x = -1, y = -1;
    findEmptyCell(x, y);
    if((x == -1) || (y == -1)) {
        QMessageBox::warning(this, "Error", "No empty cell.");
        return;
    }
    Cell* cell;
    bool flag = false;
    if(event->key() == Qt::Key_Up) {
        if(x != 3) {
            flag = true;
            cell = (Cell*)cellsLayout->itemAtPosition(x + 1, y)->widget();
        }
    } else if(event->key() == Qt::Key_Down) {
        if(x != 0) {
            flag = true;
            cell = (Cell*)cellsLayout->itemAtPosition(x - 1, y)->widget();
        }
    } else if(event->key() == Qt::Key_Right) {
        if(y != 0) {
            flag = true;
            cell = (Cell*)cellsLayout->itemAtPosition(x, y - 1)->widget();
        }
    } else if(event->key() == Qt::Key_Left) {
        if(y != 3) {
            flag = true;
            cell = (Cell*)cellsLayout->itemAtPosition(x, y + 1)->widget();
        }
    }
    if(flag) {
        cellsLayout->removeWidget(cell);
        cellsLayout->addWidget(cell, x, y);
        if (isWin()) {
            winMessage();
        }
    }
    QDialog::keyPressEvent(event);
}

void Fifteen::loadImage() {
    assemble();
    QString path = QFileDialog::getOpenFileName(this, tr("Load image"));
    if(path.isEmpty()) {
        return;
    }
    QImage image;
    if(!image.load(path)) {
        QMessageBox::warning(this, tr("Error"), tr("Not supported image format!"));
        return;
    }
    int width = image.width();
    int height = image.height();
    int cellWidth = width / 4;
    int cellHeight = height / 4;
    for(int x = 0; x < 4; ++x) {
        for(int y = 0; y < 4; ++y) {
            if(x == 3 && y == 3) {
                break;
            }
            QImage tempImage = image.copy(y * cellWidth, x * cellHeight, cellWidth, cellHeight);
            Cell* cell = (Cell*)(cellsLayout->itemAtPosition(x, y)->widget());
            cell->setPixmap(QPixmap::fromImage(tempImage).scaled(cell->size()));
        }
    }
}

void Fifteen::assemble() {
    Cell** cc = new Cell*[15];
    for(int i = 0; i < 15; i++) {
        cc[i] = (Cell*)(cellsLayout->itemAt(i)->widget());
    }
    for(int i = 0; i < 15; i++) {
        cellsLayout->addWidget(cc[i], cc[i]->getX(), cc[i]->getY());
    }
}

void Fifteen::setNumber() {
    assemble();
    for(int i = 0; i < 15; i++) {
        Cell* cell = (Cell*)(cellsLayout->itemAt(i)->widget());
        if(!cell->pixmap()) {
            delete cell->pixmap();
        }
        cell->setText(tr("%1").arg(4* cell->getX() + cell->getY() + 1));
    }
}

void Fifteen::setDefaultBackground() {
    this->setStyleSheet("QDialog {background-color: #00CCFF; font-family: Times; font-weight: bold;}");
}

void Fifteen::setBackgroundFromImage() {
    QString path = QFileDialog::getOpenFileName(this, tr("Choose image"));
    if(path.isEmpty()) {
        return;
    }
    QImage image;
    if(!image.load(path)) {
        QMessageBox::warning(this, tr("Error!"), tr("Not supported image format!"));
        return;
    }
    this->setStyleSheet(tr("QDialog {background-image: url(%1); background-clip: padding;}").arg(path));
}

Fifteen::~Fifteen() {
}
