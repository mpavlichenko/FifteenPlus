#include "engine.h"

Engine::Engine(QObject *parent) :
    QAbstractListModel(parent)
{
    shuffle();
}

void Engine::moving(int i)
{
    int empty = -1;

    if((i+1) < model.length() && model.at(i+1).someText == 0)
    {
        if((i + 1) % 4 != 0)
        {
            empty = i+1;

            beginMoveRows(QModelIndex(), i, i, QModelIndex(), empty+1);
            model.swap(i, empty);
            endMoveRows();
        }
    }
    if((i-1)>=0 && (model.at(i-1).someText == 0))
    {
        if(i % 4 != 0)
        {
            empty = i-1;

            beginMoveRows(QModelIndex(), i, i, QModelIndex(), empty);
            model.swap(i, empty);
            endMoveRows();
        }
    }
    if((i+4)<model.length() && (model.at(i+4).someText == 0))
    {
        empty = i+4;

        beginMoveRows(QModelIndex(), i, i, QModelIndex(), empty);
        model.swap(i, empty);
        endMoveRows();

        beginMoveRows(QModelIndex(), empty, empty, QModelIndex(), i);
        endMoveRows();
    }
    if((i-4)>=0 && (model.at(i-4).someText == 0))
    {
        empty = i-4;

        beginMoveRows(QModelIndex(), empty, empty, QModelIndex(), i);
        model.swap(i, empty);
        endMoveRows();

        beginMoveRows(QModelIndex(), i, i, QModelIndex(), empty);
        endMoveRows();
    }
}

bool Engine::isWin()
{
    QList<int> grid;

    for(int i = 0; i < model.length()-1; i++)
        grid << model.at(i).someText;

    int j = 0;

    while(j < grid.length()-1)
    {
        if(grid[j] > grid[j+1]) {return false; break;}
        else return true;
        j++;
    }
}

void Engine::shuffle()
{
    int N = 0;
    do
    {
        QList<int> list;

        for(int i = 1; i <= 15; i++)
            list<<i;
//        list<<0;

        int currentIndex = list.length();
        int temporaryValue, randomIndex;

        while (currentIndex)
        {
            randomIndex = qrand() % currentIndex-- + 1;

            temporaryValue = list[currentIndex];
            list[currentIndex] = list[randomIndex];
            list[randomIndex] = temporaryValue;
        }

        beginRemoveRows(QModelIndex(), 0, model.length());
        model.clear();
        endRemoveRows();

        for(int i = 0; i < list.length(); i++)
        {
            model<<(MyList(list[i], "skyblue"));
        }
        beginInsertRows(QModelIndex(), 0, model.length());
        endInsertRows();

        model<<(MyList(0, ""));

        // is it possible to solve

        int k = 0;

        for(int i = 0; i < list.length()-1; ++i)
            for(int j = i; j < list.length(); ++j)
            {
                if(list[j] < list[i])
                    k++;
            }
        N = k;
    }
    while (N % 2 != 0);
}

QVariant Engine::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role == TextRole)
        return QVariant(model[index.row()].someText);
    if(role == ColorRole)
        return QVariant(model[index.row()].someColor);
    return QVariant();
}

QHash<int, QByteArray> Engine::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TextRole] = "someText";
    roles[ColorRole] = "someColor";
    return roles;
}

int Engine::rowCount(const QModelIndex &) const
{
    return model.size();
}
