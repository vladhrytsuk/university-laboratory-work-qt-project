#include "mainwindow.h"
#include <ctime>

MainWindow::MainWindow() {

    QHBoxLayout *pole = new QHBoxLayout;
    QVBoxLayout *pole1 = new QVBoxLayout;
    QVBoxLayout *pole2 = new QVBoxLayout;
    QVBoxLayout *pole3 = new QVBoxLayout;

    Button1 = new QPushButton("1");
    Button2 = new QPushButton("2");
    Button3 = new QPushButton("3");
    Button4 = new QPushButton("4");
    Button5 = new QPushButton("5");
    Button6 = new QPushButton("6");
    Button7 = new QPushButton("7");
    Button8 = new QPushButton("8");
    Button9 = new QPushButton("9");

    Button1->setAutoDefault(true);
    Button2->setAutoDefault(true);
    Button3->setAutoDefault(true);
    Button4->setAutoDefault(true);
    Button5->setAutoDefault(true);
    Button6->setAutoDefault(true);
    Button7->setAutoDefault(true);
    Button8->setAutoDefault(true);
    Button9->setAutoDefault(true);

    Button1->move(5,25);
    Button2->move(115,25);
    Button3->move(225,25);
    Button4->move(5,135);
    Button5->move(115,135);
    Button6->move(225,135);
    Button7->move(5,245);
    Button8->move(115,245);
    Button9->move(225,245);

    pb[0] = Button1;
    pb[1] = Button2;
    pb[2] = Button3;
    pb[3] = Button4;
    pb[4] = Button5;
    pb[5] = Button6;
    pb[6] = Button7;
    pb[7] = Button8;
    pb[8] = Button9;

    pole1->addWidget(Button1);
    pole1->addWidget(Button4);
    pole1->addWidget(Button7);

    pole2->addWidget(Button2);
    pole2->addWidget(Button5);
    pole2->addWidget(Button8);

    pole3->addWidget(Button3);
    pole3->addWidget(Button6);
    pole3->addWidget(Button9);

    pole->addLayout(pole1);
    pole->addLayout(pole2);
    pole->addLayout(pole3);
    setLayout(pole);

    connect(Button1, SIGNAL(clicked()), this, SLOT(push1()));
    connect(Button2, SIGNAL(clicked()), this, SLOT(push2()));
    connect(Button3, SIGNAL(clicked()), this, SLOT(push3()));
    connect(Button4, SIGNAL(clicked()), this, SLOT(push4()));
    connect(Button5, SIGNAL(clicked()), this, SLOT(push5()));
    connect(Button6, SIGNAL(clicked()), this, SLOT(push6()));
    connect(Button7, SIGNAL(clicked()), this, SLOT(push7()));
    connect(Button8, SIGNAL(clicked()), this, SLOT(push8()));
    connect(Button9, SIGNAL(clicked()), this, SLOT(push9()));

}

void MainWindow::push(int i){
   int n[2];
   srand(time(0));
   if (pb[i]->isEnabled()) pb[i]->setDisabled(true);
   else pb[i]->setDisabled(false);

   for(int i = 0; i < 2; i++){
    n[i] = rand()%8;
    if (pb[n[i]]->isEnabled()) pb[n[i]]->setDisabled(true);
    else  pb[n[i]]->setDisabled(false);
    }
}

void MainWindow::push1(){ push(0);}
void MainWindow::push2(){ push(1);}
void MainWindow::push3(){ push(2);}
void MainWindow::push4(){ push(3);}
void MainWindow::push5(){ push(4);}
void MainWindow::push6(){ push(5);}
void MainWindow::push7(){ push(6);}
void MainWindow::push8(){ push(7);}
void MainWindow::push9(){ push(8);}
