#ifndef MYLIST_H
#define MYLIST_H
#include <QObject>

class MyList
{
    friend class Engine;

public:
    MyList(int someText, QString someColor);

private:
    int someText;
    QString someColor;
};

#endif // MYLIST_H
