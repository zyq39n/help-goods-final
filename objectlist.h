#ifndef OBJECTLIST_H
#define OBJECTLIST_H
#include <QString>
#include <QFile>
#include <QDir>
#include <QDebug>

struct objectNode
{
    QString name,information,owner,atb1,atb2,atb3;
    int rank;
    objectNode *next;
    objectNode(const QString &a, const QString &b, const QString &c, const QString & d, const QString &e, const QString f, const int g)
    {
        name =a;
        information=b;
        owner=c;
        atb1=d;
        atb2=e;
        atb3=f;
        rank=g;
    };
    objectNode():next(NULL) {}
    objectNode(const objectNode &x)
    {
        name=x.name;
        information=x.information;
        owner=x.owner;
        atb1=x.atb1;
        atb2=x.atb2;
        atb3=x.atb3;
        rank=x.rank;
    }
    ~objectNode() {}
};

class ObjectList
{
private:
    objectNode *data;
    int currentLength;
    int maxSize;
    void doubleSpace();
public:
    ObjectList(int initSize=100);
    ~ObjectList()
        {delete []data;}
    void clear();
    int length()const
        {
            return currentLength;
        }
    void insert(int i,const objectNode &x);
    void remove(int i);
    void append(const objectNode &x);
    void readTXT();
    void saveTXT();
    int search(const QString &x)const;
    objectNode visit(int i)const;
};

#endif // OBJECTLIST_H
