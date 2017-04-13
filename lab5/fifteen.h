#ifndef FIFTEEN_H
#define FIFTEEN_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QKeyEvent>
#include <QSettings>

#include <cell.h>

class Fifteen : public QDialog
{
    Q_OBJECT

public:
    Fifteen(QWidget *parent = 0);
    ~Fifteen();

public slots:
    void cellPressed();
    void mix();
    void loadImage();
    void assemble();
    void setNumber();
    void setDefaultBackground();
    void setBackgroundFromImage();
    void statistic();
    void myFunction();
    void level3();
    void level4();
    void level5();

private:
    void findEmptyCell(int &x, int &y);
    bool isWin();
    void winMessage();
    void createActions();
    void createMenu();
    void keyPressEvent(QKeyEvent *event);
    void saveStatistic();

private:
    int game;
    int win;
    QGridLayout *cellsLayout;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QMenu *gameLevel;
    QMenu *setBackgroundMenu;
    QAction *newGameAction;
    QAction *assembleAction;
    QAction *exitAction;
    QAction *loadImageAction;
    QAction *setNumberAction;
    QAction *statisticAction;
    QAction *setDefaultBackgroundAction;
    QAction *setBackgroundFromImageAction;
    QAction *cellCount;
    QAction *level3x3;
    QAction *level4x4;
    QAction *level5x5;
};

#endif // FIFTEEN_H
