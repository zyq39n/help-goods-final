#include "userlist.h"

UserList::UserList(int initSize)
{
    data=new userNode[initSize];
    maxSize=initSize;
    currentLength=0;
}

void UserList::doubleSpace()
{
    userNode *tmp=data;
    maxSize*=2;
    data=new userNode[maxSize];
    for(int i=0;i<currentLength;++i) data[i]=tmp[i];
    delete[]tmp;
}

void UserList::clear()
{

    currentLength=0;
}

//插入到第i位后
void UserList::insert(int i,const userNode &x)
{
    if (currentLength==maxSize) doubleSpace();
    for (int j=currentLength;j>i;--j) data[j]=data[j-1];
    data[i]=x;
    ++currentLength;
}

//插入到最后
void UserList::append(const userNode &x)
{
    insert(currentLength,x);
}

void UserList::remove(int i)
{
    for(int j=i;j<currentLength-1;++j) data[j]=data[j+1];
    --currentLength;
}

int UserList::search(const QString &x)const
{
    int i=0;
    for (i=0;i<currentLength&&data[i].name!=x;++i);
    if(i==currentLength) return -1;
    else return i;
}

userNode UserList::visit(int i)const
{
    return data[i];
}

int* UserList::searchByAuthority(int i)
{
    int *a = new int[currentLength];
    for (int j=0; j<currentLength; ++j)
    {
        a[j]=0;
        if (data[j].authority == i) ++a[j];
    }
    return a;
}

void UserList::addUser(const QString &x)
{
    int i = search(x);
    data[i].authority = 1;
}

void UserList::readTXT()
{
    QString path2 = QDir::currentPath() + "/userList.txt";
    QFile file2(path2);
    file2.open(QIODevice::ReadOnly);
    userNode user1;
    QString string1;
    QStringList list1;
    while (!file2.atEnd())
    {
        string1 = file2.readLine();
        list1 = string1.split("~");
        user1.name = list1[0];
        user1.password = list1[1];
        user1.phone = list1[2];
        user1.mail = list1[3];
        user1.adress = list1[4];
        user1.authority = list1[5].toInt();
        user1.objectNum = list1[6].toInt();//toInt同时去掉了最后的换行符
        append(user1);
    }
}

void UserList::saveTXT()
{
     QString path2 = QDir::currentPath() + "/userList.txt";
     QFile file2(path2);
     file2.open(QIODevice::WriteOnly);
     QTextStream out(&file2);
     for (int i=0; i<currentLength; ++i)
     {
         out << data[i].name << "~" << data[i].password << "~" << data[i].phone << "~" << data[i].mail << "~"
             << data[i].adress << "~" << data[i].authority << "~" << data[i].objectNum << "\n";
     }
     file2.close();
}
