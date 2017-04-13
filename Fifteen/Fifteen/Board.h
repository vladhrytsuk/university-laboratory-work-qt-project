#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include <QWidget>
class QGridLayout;
class QPoint;
class QPushButton;
class QPixmap;

class Board : public QWidget
{
	Q_OBJECT
public:
    Board(int cb = 4, QWidget* parent = nullptr);
    Board(const QPixmap& pixmap, int cb = 4,  QWidget* parent = nullptr);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    ~Board();


    /*void setPixMap(const QPixmap& pixmap);
    void setPixMap(const QPixmap* pixmap);*/
    bool setImage();

private:
	QList<QPushButton*> buttons;
	QList<int> numbers;
    QGridLayout* gameGridLayout;
    QPoint emptyButtonPoint;
    QPixmap* imagePixMap;

    bool image;

    int boardHeight;
	unsigned int clicks;

    void createButton(int number, int posX, int posY);
    void createImageButton(int number, int posX, int posY);
    void moveButton(QPushButton* btn, QPoint from, QPoint to);

    void createBoard();
    void randomizeBoard();
	void checkGameOver();
	int size() const;

public slots:
	void moveClicked();

signals:
    void moveMade();
    void gameWon();
};

#endif
