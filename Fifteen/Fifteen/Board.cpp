#include "Board.h"
#include "MainWindow.h"
#include <QtGlobal>
#include <QDebug>
#include <QGridLayout>
#include <QPoint>
#include <QPushButton>
#include <QTime>
#include <QPixmap>
#include <QIcon>
#include <stdexcept>
#include <QMessageBox>

#include <cstdlib> // for rand()

#define DEBUG

static int count = 0;

Board::Board(int cb, QWidget* parent) : QWidget(parent), boardHeight(cb)
{
    QTime midnight(0, 0, 0);
    srand(midnight.secsTo(QTime::currentTime()));

    gameGridLayout = new QGridLayout(this);
    gameGridLayout->setHorizontalSpacing(1);
    gameGridLayout->setVerticalSpacing(1);
    gameGridLayout->setContentsMargins(1, 1, 1, 1);
    image = false;
    imagePixMap = nullptr;

    randomizeBoard();

    createBoard();

    setLayout(gameGridLayout);
}

Board::Board(const QPixmap &pixmap, int cb, QWidget *parent) : QWidget(parent), boardHeight(cb)
{
    QTime midnight(0, 0, 0);
    srand(midnight.secsTo(QTime::currentTime()));

    gameGridLayout = new QGridLayout(this);
    gameGridLayout->setHorizontalSpacing(1);
    gameGridLayout->setVerticalSpacing(1);
    gameGridLayout->setContentsMargins(1, 1, 1, 1);

    image = true;
    imagePixMap = new QPixmap(pixmap);

    randomizeBoard();

    createBoard();

    setLayout(gameGridLayout);
}

void Board::moveUp()
{
    int y_empty = emptyButtonPoint.y();
    int x_empty = emptyButtonPoint.x();
    if (y_empty != 0) {
        QPushButton* button = static_cast<QPushButton*>(gameGridLayout->itemAtPosition(--y_empty, x_empty)->widget());
        if (button->isEnabled())
            moveButton(button, QPoint(x_empty, y_empty), emptyButtonPoint);
    }
}

void Board::moveDown()
{
    int y_empty = emptyButtonPoint.y();
    int x_empty = emptyButtonPoint.x();
    if (y_empty < boardHeight - 1) {
        QPushButton* button = static_cast<QPushButton*>(gameGridLayout->itemAtPosition(++y_empty, x_empty)->widget());
        if (button->isEnabled())
            moveButton(button, QPoint(x_empty, y_empty), emptyButtonPoint);
    }
}

void Board::moveLeft()
{
    int y_empty = emptyButtonPoint.y();
    int x_empty = emptyButtonPoint.x();
    if (x_empty != 0) {
        QPushButton* button = static_cast<QPushButton*>(gameGridLayout->itemAtPosition(y_empty, --x_empty)->widget());
        if (button->isEnabled())
            moveButton(button, QPoint(x_empty, y_empty), emptyButtonPoint);
    }
}

void Board::moveRight()
{
    int y_empty = emptyButtonPoint.y();
    int x_empty = emptyButtonPoint.x();
    if (x_empty < boardHeight - 1) {
        QPushButton* button = static_cast<QPushButton*>(gameGridLayout->itemAtPosition(y_empty, ++x_empty)->widget());
        if (button->isEnabled())
            moveButton(button, QPoint(x_empty, y_empty), emptyButtonPoint);
    }
}

Board::~Board()
{
    delete imagePixMap;
}

void Board::moveClicked()
{
	int x, y, rs, cs;
	QPushButton* clickedBtn = static_cast<QPushButton*>(sender());
    gameGridLayout->getItemPosition(gameGridLayout->indexOf(clickedBtn), &y, &x, &rs, &cs);

    if ((emptyButtonPoint.x() == x && (emptyButtonPoint.y() == y + 1 || emptyButtonPoint.y() == y - 1))
        || (emptyButtonPoint.y() == y && (emptyButtonPoint.x() == x + 1 || emptyButtonPoint.x() == x - 1))) // valid button, move it
	{
		// remove the widget from the actual position
        // and re-add it to where the emptyButtonPoint has been
        moveButton(clickedBtn, QPoint(x, y), emptyButtonPoint);
        //qDebug() << "move clicked " << count++ << endl;
	}
}

void Board::checkGameOver()
{
    Q_ASSERT(gameGridLayout->count() == numbers.size());

    // check whether the path is the last item in the grid
    if (emptyButtonPoint.y() == gameGridLayout->rowCount() - 1 && emptyButtonPoint.x() == gameGridLayout->columnCount() - 1)
    {
        //qDebug() << "Yeah\n";

        int i = 1, n = 0;

        // check whether the buttons are placed upwardly from 1 to n
        for (int y = 0; y < gameGridLayout->rowCount(); ++y) // row
            for (int x = 0; x < gameGridLayout->columnCount(); ++x) // column
            {
                if (gameGridLayout->itemAtPosition(y, x) == 0)
                    continue;
                n = numbers.indexOf(i++);
                if (buttons[n] != (QPushButton*)gameGridLayout->itemAtPosition(y, x)->widget())
                    return;
            }
        // game over:

        // stop the timer
        static_cast<MainWindow*>(parentWidget())->stopTimer();

        QMessageBox::information(this, tr("WIN!"), tr("Congratulations!!\nYou won!!"));

        // disable all the buttons
        for (QList<QPushButton*>::const_iterator it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->setDisabled(true);

        emit gameWon();
    }
}

void Board::createButton(int number, int x, int y)
{
    QPushButton* btn = new QPushButton(QString("%1").arg(number));
    btn->setFixedSize(70, 70);
    btn->setStyleSheet(QString("background: #FAFAFA; border: 1px solid #AAA;"));
    buttons << btn;
    connect(btn, SIGNAL(clicked()), this, SLOT(moveClicked()));
    gameGridLayout->addWidget(btn, y, x);
}

void Board::createImageButton(int number, int x, int y)
{
    if(!imagePixMap) throw std::runtime_error("Image not set");

    QPushButton* btn = new QPushButton;

    int imgWidth = imagePixMap->width() / boardHeight;
    int imgHeight = imagePixMap->height() / boardHeight;

    --number;

    int imagePosY = (number / boardHeight); //* imgHeight;
    int imagePosX = (number - imagePosY * boardHeight);// * imgWidth;

   //QIcon icon(imagePixMap);
    QIcon icon(imagePixMap->copy(imagePosX * imgWidth, imagePosY * imgHeight, imgWidth, imgHeight));
    btn->setIcon(icon);
    btn->setFixedSize(imgWidth, imgHeight);
    btn->setIconSize(btn->size());

    buttons << btn;
    connect(btn, SIGNAL(clicked()), this, SLOT(moveClicked()));

    gameGridLayout->addWidget(btn, y, x);
}

void Board::moveButton(QPushButton *btn, QPoint from, QPoint to)
{
    gameGridLayout->removeWidget(btn);
    gameGridLayout->addWidget(btn, to.y(), to.x());
    emptyButtonPoint = from;
    emit moveMade();
    checkGameOver();
    setFocus();
}

void Board::createBoard() {

    delete gameGridLayout;
    gameGridLayout = new QGridLayout(this);
    QList<int>::iterator it = numbers.begin();

    for (int y = 0; y < boardHeight; ++y) // row
        for (int x = 0; x < boardHeight; ++x) // column
        {
            if (emptyButtonPoint.x() == x && emptyButtonPoint.y() == y)//empty block
                continue;
            imagePixMap ? createImageButton(*(it++), x, y) : createButton(*(it++), x, y);

        }
}

void Board::randomizeBoard()
{
#ifdef DEBUG
    numbers.clear();

    for (int i = 1; i <= size(); i++)
    { // random numbers from
        numbers << i;
    }

    emptyButtonPoint.setX(boardHeight - 2);
    emptyButtonPoint.setY(boardHeight - 1);
#else
    bool oddBoard = (boardHeight % 2 == 1);

    int n;
    do
    {
        numbers.clear();

        for (int i = 0; i < size(); i++)
        { // random numbers from
            do n = rand() % size() + 1; // add 1, mod returns in range (0, size()-1)
            while (numbers.contains(n));
            numbers << n;
        }

        n = 0;

        // check for which path-row is this random placement solvable
        for (int i = 2; i <= size(); i++) {
            int index = numbers.indexOf(i);
            for (int j = 0; j < index; j++)
            {
                if (numbers[j] < i)
                {
                    ++n;
                }
            }
        }
        // if this is oddBoard, we need "n" to be even
    } while (oddBoard ? n % 2 != 0 : false);

    /* generate a random even or odd row position of the initial path, depending on "n"
    if this is oddBoard, just skip the checks (it doesn't matter) */
    do emptyButtonPoint.setY(rand() % boardHeight);
    while (oddBoard ? false : n % 2 != emptyButtonPoint.y() % 2);

    emptyButtonPoint.setX(rand() % boardHeight);
#endif

}

/*void Board::setPixMap(const QPixmap *pixmap)
{
    imagePixMap = new QPixmap(*pixmap);
    image = true;
    createBoard();
}

void Board::setPixMap(const QPixmap &pixmap)
{
    imagePixMap = new QPixmap(pixmap);
    image = true;
    createBoard();
}*/

int Board::size() const
{
    return boardHeight*boardHeight - 1;
}
