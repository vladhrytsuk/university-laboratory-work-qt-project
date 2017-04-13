#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstring>
using namespace std;
class Coll
{
public:
char value[40][10];
int connection[40][2];
int typeConnection[100];
int amount;
};
int main()
{
SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Coll a[500];
    char str[100],table[100][100];
    int index[1000],k=0,z=0;
        cout << "¬ведите путь к файлу:"<< endl;
//        cin >> str;
strcpy(str,"L:\\Lab1.txt");
    FILE *File = fopen(str, "rb");
    index[0] = (int)fgetc(File);
    int i=1,j=0,i1=0,m[100];
    while (!feof(File)) {
        index[i] = (int)fgetc(File);
        if (index[i]==32) {
            strcpy(table[j]," ");
                        k=0;
            for (int j1=i1;j1<i;j1++)
            {
        table[j][k]=(char)index[j1];
        k++;
            }
table[j][k]='\0';
m[j]=(int)index[i1]+(int)index[i-1];
z=0;
for (int j1=0;j1<j;j1++)
if (m[j]==m[j1])
{if(table[j1][0]!='&')
{strcpy(a[m[j]].value[0],table[j1]);
a[m[j]].amount=1;
table[j1][0]='&';
table[j1][1]=(char)(m[j]/100+48); z=m[j]-m[j]/100*100;
table[j1][2]=(char)(z/10+48); z=m[j]-m[j]/10*10;
table[j1][3]=(char)(z+48);
table[j1][4]='\0';
for (int i2=0;i2<=39;i2++)
{a[m[j]].connection[i2][0]=-1;
a[m[j]].connection[i2][1]=-1;
}
}
strcpy(a[m[j]].value[a[m[j]].amount],table[j]);
z=0;
while (z!=-1)
{
if (strcmp(a[m[j]].value[z],table[j])<0)
{if (a[m[j]].connection[z][0]==-1) {a[m[j]].connection[z][0]=a[m[j]].amount; z=-1;}
else z=a[m[j]].connection[z][0];}
else {if (a[m[j]].connection[z][1]==-1) {a[m[j]].connection[z][1]=a[m[j]].amount;z=-1;}
else z=a[m[j]].connection[z][1];}
}
a[m[j]].amount++;
z=1; break;}
if (z==0)
{cout << m[j]<< endl;
        j++;}
        i1=i+1;}
                i++;
    }
    if (index[i]!=32) {
            strcpy(table[j]," ");
                        k=0;
            for (int j1=i1;j1<i-1;j1++)
            {
        table[j][k]=(char)index[j1];
        k++;
            }
                m[j]=(int)index[i1]+(int)index[i-2];
                cout << m[j]<< endl;
            table[j][k]='\0';
for (int j1=0;j1<j;j1++)
if (m[j]==m[j1])
{if(table[j1][0]!='&')
{strcpy(a[m[j]].value[0],table[j1]);
a[m[j]].amount=1;
table[j1][0]='&';
table[j1][1]=(char)(m[j]/100+48); z=m[j]-m[j]/100*100;
table[j1][2]=(char)(z/10+48); z=m[j]-m[j]/10*10;
table[j1][3]=(char)(z+48);
table[j1][4]='\0';
for (int i2=0;i2<=39;i2++)
{a[m[j]].connection[i2][0]=-1;
a[m[j]].connection[i2][1]=-1;
}
}
strcpy(a[m[j]].value[a[m[j]].amount],table[j]);
z=0;
while (z!=-1)
{
if (strcmp(a[m[j]].value[z],table[j])<0)
{if (a[m[j]].connection[z][0]==-1) {a[m[j]].connection[z][0]=a[m[j]].amount; z=-1;}
else z=a[m[j]].connection[z][0];}
else {if (a[m[j]].connection[z][1]==-1) {a[m[j]].connection[z][1]=a[m[j]].amount;z=-1;}
else z=a[m[j]].connection[z][1];}
}
a[m[j]].amount++;
z=1; break;}
if (z==0)
{cout << m[j]<< endl;
        j++;}
        i1=i+1;}
for (int j1=0;j1<a[465].amount;j1++)
cout <<j1<< ") "<<a[465].value[j1] <<" влево " <<a[465].connection[j1][0] << " вправо " <<a[465].connection[j1][1]<<  endl;
/*for (int j1=0;j1<j;j1++)
cout << table[j1] << endl;*/
int k1=0,ide=0;
unsigned char search[100];
while (k1==0)
{
int am=0;
char path[40][10],p[40][7];
cout << "¬ведите искомый идентификатор:" << endl;
cin >> search;
ide=abs((int)search[0])+abs((int)search[strlen(search)-1]);
cout << ide << endl;
for (int j1=0; j1<j;j1++)
if (ide==m[j1])
{if (strcmp(search,table[j1])==0)
{cout << "—овпадение найдено в основной таблице под индексом "<< j1<< endl; break;}
else if(table[j1][0]=='&')
{z=0;
while (z!=-1)
{if (strcmp(a[m[j1]].value[z],search)==0) {z==-1;cout << "—овпадение найдено в бинарном дереве, которое находитс¤ в таблице под индексом "<< j1 << endl;
cout << "ѕуть: ";
for (int j2=0; j2<am;j2++)
cout << path[j2]<<" " << p[j2] << " ";
cout<< endl;
j1=j;break;}
if (strcmp(a[m[j1]].value[z],search)<0)
{if (a[m[j1]].connection[z][0]==-1) {z==-1;cout << "—овпадений не найдено!" << endl;j1=j; break;}
else {strcpy(path[am],a[m[j1]].value[z]);z=a[m[j1]].connection[z][0];strcpy(p[am],"влево"); am++;}}
else {if (a[m[j1]].connection[z][1]==-1) {z==-1;cout << "—овпадений не найдено!" << endl;j1=j; break;}
else {strcpy(path[am],a[m[j1]].value[z]);z=a[m[j1]].connection[z][1];strcpy(p[am],"вправо");am++; }}
}}
else if(j!=j1){cout << "—овпадений не найдено!" << endl; break;}
if(j!=j1) cout << "—овпадений не найдено!" << endl; break;
}
cout <<"¬ведите 0, чтобы запустить ещЄ один поисковый запрос. ¬ведите другое значение,чтобы завершить программу:" << endl;
cin >> k1;
}
    system("pause");
    return 0;
}
//---------------------------------------------------------------------------
