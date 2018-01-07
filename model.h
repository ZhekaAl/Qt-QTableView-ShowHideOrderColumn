#ifndef MODEL_H
#define MODEL_H


#include <QAbstractItemModel>
#include <QList>


class Model:public QAbstractTableModel
{
public:
    Model(QObject *parent = 0);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
private:
    QList<QList<int>> lst;
};

#endif // MODEL_H
