#include "mainwindow.h"
#include <QMessageBox>
#include <QList>

TableDialog::TableDialog(const QString &tableName,const QString &tableName1, QWidget *parent) :
    QDialog(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QVBoxLayout *table = new QVBoxLayout(this);
    QVBoxLayout *button = new QVBoxLayout(this);
    QVBoxLayout *lineedit = new QVBoxLayout(this);
    QVBoxLayout *select = new QVBoxLayout(this);

    QVBoxLayout *layout2 = new QVBoxLayout(this);

    tablename=tableName;
    tablename1=tableName1;

    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model1 = new QSqlTableModel(this);
    model1->setTable(tableName1);
    model1->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model1->select();
    model->submitAll();

    view = new QTableView;
    view->setModel(model);
    view1 = new QTableView;
    view1->setModel(model1);

    table->addWidget(view);
    table->addWidget(view1);

    pb = new QPushButton("Добавить ряд для 1-й таблицы", this);
    QPushButton *pb1 = new QPushButton("Добавить ряд для 2-й таблицы", this);
    submitButton= new QPushButton("Отправить",this);
    revert = new QPushButton("Отменить",this);
    QPushButton *addF1= new QPushButton("Вставить",this);
    QPushButton *push=new QPushButton("Выбор 1",this);
    QPushButton *push1=new QPushButton("Выбор 2",this);

    text=new QLineEdit(this);
    text1=new QLineEdit(this);
    text2=new QLineEdit(this);
    text3=new QLineEdit(this);
    text4=new QLineEdit(this);
    select1=new QLineEdit("All_Employees",this);
    select2=new QLineEdit("Month",this);

    textedit=new QTextEdit(this);

    select->addWidget(select1);
    select->addWidget(select2);
    select->addWidget(textedit);
    textedit->setDisabled(true);

    select->addWidget(push);
    select->addWidget(push1);

    lineedit->addWidget(text);
    text->setText("Введите название таблицы <fio> или <vid>");
    lineedit->addWidget(text1);
    text1->setText("Введите данные");
    lineedit->addWidget(text2);
    text2->setText("Введите данные");
    lineedit->addWidget(text3);
    text3->setText("Введите данные");
    lineedit->addWidget(text4);
    text4->setText("Введите данные");
    lineedit->addWidget(addF1);

    button->addWidget(pb);
    button->addWidget(pb1);
    button->addWidget(submitButton);
    button->addWidget(revert);

    layout2->addLayout(button);
    layout2->addLayout(lineedit);

    layout->addLayout(table);
    layout->addLayout(layout2);
    layout->addLayout(select);
    setLayout(layout);

    connect(pb, SIGNAL(clicked()), this, SLOT(addRow()) );
    connect(pb1, SIGNAL(clicked()), this, SLOT(addRow1()) );
    connect(revert,SIGNAL(clicked()),model,SLOT(revertAll()));
    connect(revert,SIGNAL(clicked()),model1,SLOT(revertAll()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
    connect(addF1, SIGNAL(clicked()), this, SLOT(addData()));
    connect(push,SIGNAL(clicked()),this,SLOT(sel()));
    connect(push1,SIGNAL(clicked()),this,SLOT(sel1()));

}

//ряд для 1 таблицы
void TableDialog::addRow(){
    int lastRow = model->rowCount();
    model->insertRow(lastRow);
    model->setData(model->index(lastRow,1),"");

}
//ряд для 2 таблицы
void TableDialog::addRow1(){
    int lastRow = model1->rowCount();
    model1->insertRow(lastRow);
    model1->setData(model1->index(lastRow,1),"");

}

//отправка данных бд
void TableDialog::submit()
{
    model->database().transaction();
    model1->database().transaction();
    if (model->submitAll()&&model1->submitAll()) {
        model->database().commit();
        model1->database().commit();
    } else {
        model->database().rollback();
        model1->database().rollback();

    }
}

//добавление данных в таблицу с lineedit
void TableDialog:: addData(){

    QSqlQuery query;
    QString str=text->text();
    if(str == tablename1){
    query.prepare("INSERT INTO "+str+" (id, vid, month, summa) VALUES ( :id,:vid,:month,:summa)");
    query.bindValue(":id",text1->text().toInt());
    query.bindValue(":vid",text2->text());
    query.bindValue(":month",text3->text().toInt());
    query.bindValue(":summa",text4->text().toFloat());
    bool b=query.exec();
       if (!b) {
           qDebug() << "Unable to do insert opeation";
       }

     model1->submitAll();
}
    else if(str == tablename){
        query.prepare("INSERT INTO "+str+" (id, family, name, otch) VALUES ( :id,:fam,:name,:otch)");
        query.bindValue(":id",text1->text().toInt());
        query.bindValue(":fam",text2->text());
        query.bindValue(":name",text3->text());
        query.bindValue(":otch",text4->text());
        bool b=query.exec();
           if (!b) {
               qDebug() << "Unable to do insert opeation";
           }


        model->submitAll();
    }
    else qDebug()<<"Incorecct table";

}

//выборка по имени зарплаты
void TableDialog:: sel(){
    textedit->setText("");
    QList<int> forID;
    QList<int> forID2;
    QList<float> forSumm;
    QList<QString> forFam;
    QList<QString> forFam2;
    QString str=select1->text();
    int id;
    QSqlQuery query;
    if(str!="All_Employees"){
    query.prepare("SELECT id, family FROM fio WHERE family = :fam");
    query.bindValue(":fam", str);
    if(!query.exec())
        qDebug()<<"Err";

    else
    while (query.next()) {
           id=query.value(0).toInt();
           forID<<id;
           forFam<<query.value(1).toString();



     }
    QList<int>::iterator it = forID.begin();
    QList<QString>::iterator it2 = forFam.begin();
    while(it!=forID.end()){
     query.prepare("SELECT summa FROM vid WHERE id = :id");
     query.bindValue(":id",*it);
     if(query.exec())
         while (query.next()){
            forSumm<<query.value(0).toFloat();
            forFam2<<*it2;
            forID2<<*it;
         }
    ++it;
    ++it2;
    }
     QList<int>::iterator it3 = forID2.begin();
     QList<float>::iterator it1 = forSumm.begin();
     QList<QString>::iterator it4 = forFam2.begin();
     while (it1!=forSumm.end()) {
          qDebug() <<*it3 <<" " << *it4<<" "<<*it1;
          textedit->insertPlainText(QString("ID: ")+QString::number(*it3)+QString(" is: ")+QString(*it4)+QString(" has summa: ")+QString::number(*it1)+QString("\n"));
          ++it3;
          ++it1;
          ++it4;
     }
    forID.clear();
    forID2.clear();
    forSumm.clear();
    forFam.clear();
    forFam2.clear();
    }
    else{
        query.exec("SELECT id, family FROM fio");
        while (query.next()) {
              forID<<query.value(0).toInt();
             forFam<<query.value(1).toString();
              //qDebug() << id<<" "<<fam;
             //textedit->insertPlainText(QString::number(id)+QString(" ")+QString(fam)+QString("\n"));
         }
        QList<int>::iterator it = forID.begin();
        QList<QString>::iterator it2 = forFam.begin();
        while(it!=forID.end()){
        query.prepare("SELECT summa FROM vid WHERE id = :id");
        query.bindValue(":id",*it);
        if(query.exec())
            while (query.next()) {
            forSumm<<query.value(0).toFloat();
            forFam2<<*it2;
            forID2<<*it;
          }
        ++it;
        ++it2;
        }
        forID.clear();
        forFam.clear();
        QList<float>::iterator it1 = forSumm.begin();
        QList<QString>::iterator it3 = forFam2.begin();
        QList<int>::iterator it4 = forID2.begin();
        while (it1!=forSumm.end()) {
             qDebug() <<*it4 <<" " << *it3<<" "<<*it1;
             textedit->insertPlainText(QString("ID: ")+QString::number(*it4)+QString(" is: ")+QString(*it3)+QString(" has summa: ")+QString::number(*it1)+QString("\n"));
             ++it1;
             ++it3;
             ++it4;
        }
    }

}

//выборка по фамилии (и месяцу) вида работы .... вывод зар. платы за месяц по каждому работнику
void TableDialog:: sel1(){
    textedit->setText("");
    QList<int> forID;
    QList<int> forID2;
    QList<int> forMonth;
    QList<QString> forVid;
    QList<QString> forFam;
    QList<QString> forFam2;
    QString str=select1->text();
    int id;
    QSqlQuery query,query1;
    if(str!="All_Employees"&&select2->text()!=NULL){
    query.prepare("SELECT id, family FROM fio WHERE family = :fam");
    query.bindValue(":fam", str);
    if(!query.exec())
        qDebug()<<"Err";

    else
    while (query.next()) {
           id=query.value(0).toInt();
           forID<<id;
           forFam<<query.value(1).toString();
    }
    QList<int>::iterator it = forID.begin();
    QList<QString>::iterator it2 = forFam.begin();
    while(it!=forID.end()){
     query.prepare("SELECT vid, month FROM vid WHERE id = :id AND month = :mon");
     query.bindValue(":id",*it);
     query.bindValue(":mon",select2->text().toInt());
     if(query.exec())
         while (query.next()){
            forVid<<query.value(0).toString();
            int m =  query.value(1).toInt();
            forMonth<<m;
            forFam2<<*it2;
            forID2<<*it;
       }

    ++it;
    ++it2;
    }
     QList<int>::iterator it3 = forID2.begin();
     QList<QString>::iterator it1 = forVid.begin();
     QList<QString>::iterator it4 = forFam2.begin();
     QList<int>::iterator it5 = forMonth.begin();
     while (it1!=forVid.end()) {
          qDebug() <<*it3 <<" " << *it4<<" "<<*it1;
          textedit->insertPlainText(QString("ID: ")+QString::number(*it3)+QString(" is: ")+QString(*it4)+QString(" has vid: ")+QString(*it1)+QString(", month is: ")+QString::number(*it5)+QString("\n"));
          ++it3;
          ++it1;
          ++it4;
          ++it5;
     }
    forID.clear();
    forID2.clear();
    forVid.clear();
    forMonth.clear();
    forFam.clear();
    forFam2.clear();
    }
    else if(select2->text()==NULL){
        query.exec("SELECT id, family FROM fio");
        while (query.next()) {
               id=query.value(0).toInt();
               forID<<id;
               forFam<<query.value(1).toString();
        }
        QList<int>::iterator it = forID.begin();
        QList<QString>::iterator it2 = forFam.begin();
        while(it!=forID.end()){
         query.prepare("SELECT vid, month FROM vid WHERE id = :id");
         query.bindValue(":id",*it);
            if(query.exec())
             while (query.next()){
                forVid<<query.value(0).toString();
                int m =  query.value(1).toInt();
                forMonth<<m;
                forFam2<<*it2;
                forID2<<*it;
               }

        ++it;
        ++it2;
        }
         QList<int>::iterator it3 = forID2.begin();
         QList<QString>::iterator it1 = forVid.begin();
         QList<QString>::iterator it4 = forFam2.begin();
         QList<int>::iterator it5 = forMonth.begin();
         while (it1!=forVid.end()) {
              qDebug() <<*it3 <<" " << *it4<<" "<<*it1;
              textedit->insertPlainText(QString("ID: ")+QString::number(*it3)+QString(" is: ")+QString(*it4)+QString(" has vid: ")+QString(*it1)+QString(", month is: ")+QString::number(*it5)+QString("\n"));
              ++it3;
              ++it1;
              ++it4;
              ++it5;
         }
        forID.clear();
        forID2.clear();
        forVid.clear();
        forMonth.clear();
        forFam.clear();
        forFam2.clear();
}
}
