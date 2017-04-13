#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Board.h"
#include <QWidget>
#include <QList>

class QHBoxLayout;
class QLabel;
class QLCDNumber;
class QSpinBox;
class QVBoxLayout;
class QGroupBox;
class QRadioButton;
class QPixmap;
class QTableWidget;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = 0);
    void stopTimer();

public slots:
    void newGame();
    void showStat();
    void updateMoves();
    void updateClock();
    void onOpenImageClick();
    void updateStatistics(QString state = "Win");

private:

    bool eventFilter(QObject *target, QEvent *event);

    QGroupBox* getSettingsGroupBox();
    Board* board;
    QHBoxLayout* lcdLayout;
    QHBoxLayout* settingsLayout;
    QHBoxLayout* newGameLayout;
    QVBoxLayout* layout;
    QLCDNumber* lcdSecs;
    QLCDNumber* lcdMoves;
    QTimer* timer;
    QSpinBox* cubesize;
    QTableWidget* statistics;

    QPixmap* imagePixelMap;

    QRadioButton* numbersSelected;
    QRadioButton* imageSelected;

    int seconds;
    int moves;
    bool win;
};

#endif
