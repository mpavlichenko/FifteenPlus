#ifndef ENGINE_H
#define ENGINE_H

#include <QAbstractListModel>
#include <QObject>
#include <QDebug>
#include <QList>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QModelIndex>
#include "mylist.h"

class Engine : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);

    enum Roles {
        TextRole = Qt::UserRole + 1,
        ColorRole = Qt::UserRole + 2,
        };

    virtual int rowCount(const QModelIndex&) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void moving(int i);
    Q_INVOKABLE void shuffle();
    Q_INVOKABLE bool isWin();

private:
    QList<MyList> model;

public slots:

signals:

};

#endif // ENGINE_H
