#include "mainwindow.h"
TableDialog::TableDialog(QWidget *parent) :
    QDialog(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QVBoxLayout *button = new QVBoxLayout(this);
    table = new QTableWidget(this);
    table->setRowCount(3);
    table->setColumnCount(3);
    textedit = new QTextEdit(this);
    textedit->resize(50,50);
    textedit->setEnabled(false);
    button->addWidget(textedit);

    layout->addWidget(table);
    clickButton = new QPushButton("Make table", this);
    button->addWidget(clickButton);
    Step1 = new QPushButton("Step1",this);
    button->addWidget(Step1);
    Step2 = new QPushButton("Step2",this);
    button->addWidget(Step2);
    Step3 = new QPushButton("Step3",this);
    button->addWidget(Step3);
    Step4 = new QPushButton("NoStep",this);
    button->addWidget(Step4);
    layout->addLayout(button);
    setLayout(layout);

    tab = false;
    step[0] = step[1] = false;


    connect( clickButton, SIGNAL(clicked()), this, SLOT(makeTable()) );


    connect(Step4, SIGNAL(clicked()),this,SLOT(delta()));
    connect(Step1, SIGNAL(clicked()),this,SLOT(delta1()));
    connect(Step2, SIGNAL(clicked()),this,SLOT(delta2()));
    connect(Step3, SIGNAL(clicked()),this,SLOT(delta3()));
    connect(table, SIGNAL(cellChanged(int, int)), this, SLOT(setToolTip(int, int)) );

    QTimer *time=new QTimer(this);
    connect(time, SIGNAL(timeout()),this,SLOT(makeTable()));
     int k=0;
    time->start(100);

   time->stop();

}




void TableDialog::makeTable(){
    QString s;

    step[0]=step[1]=false;




 //  for(;time.elapsed() < 300;) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
                QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(rand()% 120-70));
                newItem->setTextAlignment(Qt::AlignCenter);
                textedit->setText(tr("Make random matrix\n"));
                table->setItem(row, col, newItem);

                    s = table->item(row,col)->text();
                    a[row][col]=s.toInt();
                 }
          //  }
        }
 tab=true;







      }

void TableDialog::delta1(){
    if(tab == true){
    textedit->setText(tr(""));
    textedit->insertPlainText("Step 1 is: a13*a22*a31 + a11*a23*a32 + a12*a21*a33\n\nResult of step 1: ");
    b = 0;
    b = a[0][0]*a[1][1]*a[2][2]+a[0][1]*a[1][2]*a[2][0]+a[0][2]*a[1][0]*a[2][1];

    table->item(0,0)->setBackground(Qt::red);
    table->item(1,1)->setBackground(Qt::red);
    table->item(2,2)->setBackground(Qt::red);

    table->item(0,1)->setBackground(Qt::yellow);
    table->item(1,2)->setBackground(Qt::yellow);
    table->item(2,0)->setBackground(Qt::yellow);

    table->item(0,2)->setBackground(Qt::green);
    table->item(1,0)->setBackground(Qt::green);
    table->item(2,1)->setBackground(Qt::green);
    QString str;
    str = QString::number(a[0][0]) + QString(" * ")+QString::number(a[1][1]) + QString(" * ")+QString::number(a[2][2]);
    str += QString(" + ") + QString::number(a[0][1]) + QString(" * ")+QString::number(a[1][2]) + QString(" * ")+QString::number(a[2][0]);
    str += QString(" + ") + QString::number(a[0][2]) + QString(" * ")+QString::number(a[1][0]) + QString(" * ")+QString::number(a[2][1]);
    strs3 = str;
    str += QString(" = ") + QString::number(b);
    textedit->insertPlainText(str);
    step[0] = true;
    }
    else textedit->setText(tr("Make table"));

}
void TableDialog::delta2(){
    if(tab == true){
        if(step[0]==true){
    textedit->setText(tr(""));
    textedit->insertPlainText("Step 2 is: a11*a22*a33 + a12*a23*a31 + a13*a21*a32\n\nResult of step 2: ");
    c = 0;
    c = a[0][2]*a[1][1]*a[2][0]+a[0][0]*a[1][2]*a[2][1]+a[0][1]*a[1][0]*a[2][2];
    table->item(0,2)->setBackground(Qt::red);
    table->item(1,1)->setBackground(Qt::red);
    table->item(2,0)->setBackground(Qt::red);

    table->item(0,0)->setBackground(Qt::yellow);
    table->item(1,2)->setBackground(Qt::yellow);
    table->item(2,1)->setBackground(Qt::yellow);

    table->item(0,1)->setBackground(Qt::green);
    table->item(1,0)->setBackground(Qt::green);
    table->item(2,2)->setBackground(Qt::green);

    QString str;
    str = QString::number(a[0][2]) + QString(" * ")+QString::number(a[1][1]) + QString(" * ")+QString::number(a[2][0]);
    str +=QString(" + ") + QString::number(a[0][0]) + QString(" * ")+QString::number(a[1][2]) + QString(" * ")+QString::number(a[2][1]);
    str +=QString(" + ") + QString::number(a[0][1]) + QString(" * ")+QString::number(a[1][0]) + QString(" * ")+QString::number(a[2][2]);
    strs3 +=QString(" - (")+str+QString(")");
    str +=QString(" = ") + QString::number(c);
    textedit->textCursor().movePosition(QTextCursor::End);
    textedit->insertPlainText(str);
    step[1]=true;

        }
        else textedit->setText(tr("perform step 1"));
    }
    else textedit->setText(tr("Make table"));
}

void TableDialog::delta3(){
    if(tab == true){
        if(step[1] == true){
    textedit->setText(tr(""));
    textedit->insertPlainText("Step 3 is: a11*a22*a33 + a12*a23*a31 + a13*a21*a32 - (a13*a22*a31 + a11*a23*a32 + a12*a21*a33)\n\nResult of step 3:  ");
     for (int row = 0; row<3; row++){
        for (int col= 0; col<3; col++){
            table->item(row,col)->setBackground(Qt::gray);
        }
     }
    int det = b-c;
    QString newstr;
    newstr+=strs3+QString(" = ")+QString::number(b)+QString(" - ")+QString::number(c)+QString(" = ")+QString::number(det);
    textedit->insertPlainText(newstr+QString("\n\ndet(M)=")+QString::number(det));
    newstr =QString::null;
        }
        else textedit->setText(tr("perform step 2"));
    }
    else textedit->setText(tr("Make table"));

}
void TableDialog::delta(){
    b = c = 0;
    if(tab == true){
    textedit->setText(tr(""));
      for (int row = 0; row<3; row++){
          if(row == 1)
              textedit->insertPlainText("det(M) =  ");
          else textedit->insertPlainText("                ");
                textedit->insertPlainText(tr("       |"));
        for (int col= 0; col<3; col++){
            table->item(row,col)->setBackground(Qt::cyan);
            textedit->insertPlainText(" \t");
            textedit->insertPlainText(table->item(row,col)->text());
        }
         if(row==1) textedit->insertPlainText(" |     =\n");
         else textedit->insertPlainText(tr(" |\n"));

      }
    b = a[0][0]*a[1][1]*a[2][2]+a[0][1]*a[1][2]*a[2][0]+a[0][2]*a[1][0]*a[2][1];
    c = a[0][2]*a[1][1]*a[2][0]+a[0][0]*a[1][2]*a[2][1]+a[0][1]*a[1][0]*a[2][2];
    int det = b-c;
    textedit->insertPlainText(QString("\n= ") + QString:: number(det));
    }
    else textedit->setText(tr("Make table"));
}

void TableDialog::setToolTip(int i, int j){
      QTableWidgetItem *changedItem = table->item(i, j);
      changedItem->setToolTip(changedItem->text());

}

void TableDialog::keyPressEvent(QKeyEvent *event) {
    QString ss = table->currentItem()->text();
    int i = table->currentRow();
    int j = table->currentColumn();
    int key=event->key();
    QString str = QString(QChar(key));
    if (key>=Qt::Key_0 && key<=Qt::Key_9) {
      table->currentItem()->setText(ss+str);
      a[i][j]=table->item(i,j)->text().toInt();
    }
    else if (key==Qt::Key_Backspace) {
        table->currentItem()->setText(ss.left(ss.length()-1));
        a[i][j]=table->item(i,j)->text().toInt();
    }
    else if (key==Qt::Key_Delete) {
        table->currentItem()->setText(ss.right(ss.length()-1));
        a[i][j]=table->item(i,j)->text().toInt();
    }
    else if (key==Qt::Key_Plus) {
         if (ss.startsWith("-")) {
           table->currentItem()->setText(ss.right(ss.length()-1));
           a[i][j]=table->item(i,j)->text().toInt();
        }
        else {
            ss = QString(" ")+ss;
            table->currentItem()->setText(ss);
        }
    }
    else if (key==Qt::Key_Minus) {
         if (!ss.startsWith("-")){
            ss = QString("-")+ss;
            table->currentItem()->setText(ss);
            a[i][j]=table->item(i,j)->text().toInt();
         }
         else {
              ss = QString(" ")+ss;
              table->currentItem()->setText(ss);
         }
    }

}
