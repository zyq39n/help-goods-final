#include "objectlist.h"

ObjectList::ObjectList(int initSize)
{
    data=new objectNode[initSize];
    maxSize=initSize;
    currentLength=0;
}

void ObjectList::doubleSpace()
{
    objectNode *tmp=data;
    maxSize*=2;
    data=new objectNode[maxSize];
    for(int i=0;i<currentLength;++i) data[i]=tmp[i];
    delete[]tmp;
}

void ObjectList::clear()
{

    currentLength=0;
}

//插入到第i位后
void ObjectList::insert(int i,const objectNode &x)
{
    if (currentLength==maxSize) doubleSpace();
    for (int j=currentLength;j>i;--j) data[j]=data[j-1];
    data[i]=x;
    ++currentLength;
}

//插入到最后
void ObjectList::append(const objectNode &x)
{
    insert(currentLength,x);
}

void ObjectList::remove(int i)
{
    for(int j=i;j<currentLength-1;++j) data[j]=data[j+1];
    --currentLength;
}

int ObjectList::search(const QString &x)const
{
    int i=0;
    for (i=0;i<currentLength&&data[i].name!=x;++i);
    if(i==currentLength) return -1;
    else return i;
}

objectNode ObjectList::visit(int i)const
{
    return data[i];
}

int *ObjectList::searchByOwner(const QString &x)
{
    int *a = new int[currentLength];
    for (int i=0; i<currentLength; ++i)
    {
        a[i]=0;
        if (data[i].owner == x) ++a[i];
    }
    return a;
}


void ObjectList::readTXT()
{
    QString path1 = QDir::currentPath() + "/objectList.txt";
    QFile file1(path1);
    file1.open(QIODevice::ReadOnly);
    objectNode object1;
    QString string1;
    QStringList list1;
    while (!file1.atEnd())
    {
        string1 = file1.readLine();
        list1 = string1.split("~");
        object1.name = list1[0];
        object1.information = list1[1];
        object1.owner = list1[2];
        object1.atb1 = list1[3];
        object1.atb2 = list1[4];
        object1.atb3 = list1[5];
        object1.rank = list1[6].toInt();//toInt同时去掉了最后的换行符
        append(object1);
    }
}

void ObjectList::saveTXT()
{
    QString path1 = QDir::currentPath() + "/objectList.txt";
    QFile file1(path1);
    file1.open(QIODevice::WriteOnly);
    QTextStream out(&file1);
    for (int i=0; i<currentLength; ++i)
    {
        out << data[i].name << "~" << data[i].information << "~" << data[i].owner << "~" << data[i].atb1 << "~"
            << data[i].atb2 << "~" << data[i].atb3 << "~" << data[i].rank << "\n";
    }
    file1.close();
}
