#ifndef USERLIST_H
#define USERLIST_H
#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>

struct userNode
    {
        QString name,password,phone,mail,adress;
        int authority,objectNum;
        userNode *next;
        userNode(const QString &a, const QString &b, const QString &c, const QString & d, const QString &e, const int f, const int g)
        {
            name =a;
            password=b;
            phone=c;
            mail=d;
            adress=e;
            authority=f;
            objectNum=g;
        };
        userNode():next(NULL) {}
        userNode(const userNode &x)
        {
            name=x.name;
            password=x.password;
            phone=x.phone;
            mail=x.mail;
            adress=x.adress;
            authority=x.authority;
            objectNum=x.objectNum;
        }
        ~userNode() {}
    };

class UserList
{
private:
    userNode *data;
    int currentLength;
    int maxSize;
    void doubleSpace();
public:
    UserList(int initSize=10);
    ~UserList()
        {delete []data;}
    void clear();
    int length()const
        {
            return currentLength;
        }
    void insert(int i,const userNode &x);
    void append(const userNode &x);
    void remove(int i);
    int search(const QString &x)const;
    int *searchByAuthority(int i);
    void readTXT();
    void saveTXT();
    userNode visit(int i)const;
    void addUser(const QString &x);

};

#endif // USERLIST_H
