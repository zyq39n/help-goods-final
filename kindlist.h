#ifndef KINDLIST_H
#define KINDLIST_H
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QDebug>

class KindList
{
    private:
        QStringList *data;//类型名，特征1名，2,3
        int currentLength;
        int maxSize;
        void doubleSpace();
    public:
        KindList(int initsize=10);
        ~KindList(){delete []data;};
        void clear();
        int length()const {return currentLength;};
        void readTXT();
        void saveTXT();
        void insert(int i,const QStringList &x);
        void remove(int i);
        int search(const QString &x)const;
        QStringList visit(int i)const;
        void append(const QStringList &x);
};

#endif // KINDLIST_H
