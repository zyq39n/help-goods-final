#include "kindlist.h"

KindList::KindList(int initSize)
{
    data=new QStringList[initSize];
    maxSize=initSize;
    currentLength=0;
}

void KindList::doubleSpace()
{
    QStringList *tmp=data;
    maxSize*=2;
    data=new QStringList[maxSize];
    for(int i=0;i<currentLength;++i) data[i]=tmp[i];
    delete[]tmp;
}

void KindList::clear()
{

    currentLength=0;
}

//插入到第i位后
void KindList::insert(int i,const QStringList &x)
{
    if (currentLength==maxSize) doubleSpace();
    for (int j=currentLength;j>i;--j) data[j]=data[j-1];
    data[i]=x;
    ++currentLength;
}

//插入到最后
void KindList::append(const QStringList &x)
{
    insert(currentLength,x);
}

void KindList::remove(int i)
{
    for(int j=i;j<currentLength-1;++j) data[j]=data[j+1];
    --currentLength;
}

int KindList::search(const QString &x)const
{
    int i=0;
    for (i=0;i<currentLength&&data[i][0]!=x;++i);
    if(i==currentLength) return -1;
    else return i;
}

QStringList KindList::visit(int i)const
{
    return data[i];
}

void KindList::readTXT()
{
    QString path3 = QDir::currentPath() + "/kindList.txt";
    QFile file3(path3);
    file3.open(QIODevice::ReadOnly);
    QString string1;
    QStringList list1;
    while (!file3.atEnd())
    {
        string1 = file3.readLine();
        list1 = string1.split("~");
        //qDebug()<<list1[3];
        list1[3]=list1[3].left(list1[3].size()-1);//删掉最后的换行符
        //qDebug()<<list1[3];
        append(list1);
    }
}

void KindList::saveTXT()
{
     QString path3 = QDir::currentPath() + "/kindList.txt";
     QFile file3(path3);
     file3.open(QIODevice::WriteOnly);
     QTextStream out(&file3);
     for (int i=0; i<currentLength; ++i)
     {
         out << data[i][0] << "~" << data[i][1] << "~" << data[i][2] << "~" << data[i][3] << "\n";
     }
     file3.close();
}
