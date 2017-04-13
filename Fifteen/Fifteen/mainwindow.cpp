#include "MainWindow.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QPixmap>
#include <QEvent>
#include <QKeyEvent>
#include <QTableWidget>
#include <QCoreApplication>
#include <QString>

MainWindow::MainWindow(QWidget* parent) : board(NULL), QWidget(parent)
{
    imagePixelMap = nullptr;
    imageSelected = nullptr;
    cubesize = nullptr;

    statistics = new QTableWidget(0, 4);

    statistics->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Result")));
    statistics->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Board size")));
    statistics->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Game time")));
    statistics->setHorizontalHeaderItem(3, new QTableWidgetItem(tr("Number of moves")));

    layout = new QVBoxLayout(this);
    lcdLayout = new QHBoxLayout;
    settingsLayout = new QHBoxLayout;
    newGameLayout = new QHBoxLayout;

    QLabel* secsLabel = new QLabel(tr("Secs:"));
    QLabel* movesLabel = new QLabel(tr("Moves:"));
    lcdSecs = new QLCDNumber(4);
    lcdSecs->setMinimumHeight(30);
    lcdMoves = new QLCDNumber(4);

    QPushButton* newgame = new QPushButton(tr("&New game"));
    connect(newgame, SIGNAL(clicked()), this, SLOT(newGame()));

    QPushButton* statisticsBtn = new QPushButton(tr("Show statistics"));
    connect(statisticsBtn, SIGNAL(clicked()), this, SLOT(showStat()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateClock()));

    newGame();

    lcdLayout->addWidget(secsLabel);
    lcdLayout->addWidget(lcdSecs, 1);
    lcdLayout->addWidget(movesLabel);
    lcdLayout->addWidget(lcdMoves, 1);

    settingsLayout->addWidget(this->getSettingsGroupBox());

    newGameLayout->addStretch();
    newGameLayout->addWidget(newgame);
    newGameLayout->addWidget(statisticsBtn);

    layout->setContentsMargins(2, 2, 2, 2);

    layout->addLayout(lcdLayout);
    layout->addLayout(settingsLayout);

    layout->addLayout(newGameLayout);

    setLayout(layout);
    QCoreApplication::instance()->installEventFilter(this);
    setFocus();
}

void MainWindow::newGame()
{

    if(!win) {
        updateStatistics("Loose");
    }

    int index = 0;
    if (board)
    {
        index = layout->indexOf(board);
        layout->removeWidget(board);
        delete board;
        stopTimer();
    }

    int size = cubesize ? cubesize->value() : 4;

    if (imagePixelMap && imageSelected->isChecked()) {
        board = new Board(*imagePixelMap, size, this);
    }
    else {
        board = new Board(size, this);
    }

    connect(board, SIGNAL(moveMade()), this, SLOT(updateMoves()));
    connect(board, SIGNAL(gameWon()), this, SLOT(updateStatistics()));

    layout->insertWidget(index, board);

    // without this old boards don't disappear if they have parent "this"
    //layout->update();
    // FIXME: this is apparently needed for resize() to set the proper size
    //board->hide();
    //board->show();

    seconds = -1;
    moves = -1;
    updateClock();
    updateMoves();

    win = false;
    resize(sizeHint());
}

void MainWindow::showStat()
{
    statistics->resizeColumnsToContents();

    int width = 0;
    for (int i = 0; i < statistics->columnCount(); ++i) {
        width += statistics->columnWidth(i);
    }
    statistics->resize(width + 30,
                       statistics->rowCount() * statistics->rowHeight(0) + 100);
    statistics->show();
}

void MainWindow::stopTimer()
{
    timer->stop();
}

void MainWindow::updateClock()
{
    lcdSecs->display(++seconds);
}

void MainWindow::onOpenImageClick()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                    tr("Open image"), "", tr("Image files (*.png, *.jpg, *.bmp)"));
    if (fileName.isEmpty())
        return;
    else {

        imagePixelMap = new QPixmap;

        if (!imagePixelMap->load(fileName)) {
            QMessageBox::information(this, tr("Unable to open image"), "");
            imagePixelMap = nullptr;
            return;
        }
        else {
            imageSelected->setEnabled(true);
        }
    }

}

void MainWindow::updateStatistics(QString state)
{

    QTableWidgetItem* GameResult = new QTableWidgetItem(state);
    QTableWidgetItem* GameSize = new QTableWidgetItem(cubesize->text());
    QTableWidgetItem* Time = new QTableWidgetItem(tr("%1").arg(lcdSecs->intValue()));
    QTableWidgetItem* Moves = new QTableWidgetItem(tr("%1").arg(lcdMoves->intValue()));
    int rowNumber = statistics->rowCount();
    statistics->insertRow(rowNumber);

    statistics->setItem(rowNumber, 0, GameResult);
    statistics->setItem(rowNumber, 1, GameSize);
    statistics->setItem(rowNumber, 2, Time);
    statistics->setItem(rowNumber, 3, Moves);
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    //qDebug() << event << endl;
    bool processed = false;
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        switch(keyEvent->key()) {
            case Qt::Key_Up:
                board->moveUp();
                processed = true;
                break;
            case Qt::Key_Down:
                board->moveDown();
                processed = true;
                break;
            case Qt::Key_Left:
                board->moveLeft();
                processed = true;
                break;
            case Qt::Key_Right:
                board->moveRight();
                processed = true;
                break;
        }
    }
    if (!processed) {
        processed = QWidget::eventFilter(target, event);
    }
    return processed;
}

QGroupBox *MainWindow::getSettingsGroupBox()
{
    QVBoxLayout* leftSettingsGroup = new QVBoxLayout;
    QVBoxLayout* rightSettingsGroup = new QVBoxLayout;
    QHBoxLayout* settingsLayout = new QHBoxLayout;

    QPushButton* openImage = new QPushButton(tr("&Open image"));
    connect(openImage, SIGNAL(clicked(bool)), this, SLOT(onOpenImageClick()));

    cubesize = new QSpinBox;
    cubesize->setRange(3, 20);
    cubesize->setValue(4);

    leftSettingsGroup->addWidget(cubesize);
    leftSettingsGroup->addWidget(openImage);

    numbersSelected = new QRadioButton(tr("&numbers"));
    imageSelected = new QRadioButton(tr("&image"));

    numbersSelected->setChecked(true);
    imageSelected->setEnabled(false);

    rightSettingsGroup->addWidget(numbersSelected);
    rightSettingsGroup->addWidget(imageSelected);

    settingsLayout->addLayout(leftSettingsGroup);
    settingsLayout->addLayout(rightSettingsGroup);

    QGroupBox* settingsGroup = new QGroupBox;

    settingsGroup->setLayout(settingsLayout);

    return settingsGroup;
}

void MainWindow::updateMoves()
{
    if (moves == 0)
        timer->start(1000);
    lcdMoves->display(++moves);
}
