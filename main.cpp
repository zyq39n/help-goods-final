#include "widget.h"
//#include <QDebug>
//#include <QStringList>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
