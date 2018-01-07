#include "model.h"

Model::Model(QObject *parent):QAbstractTableModel(parent)
{
  for(int i=0;i<100;i++)
  {
      QList<int> list;
      for(int j=0;  j<5;j++)
      {
          list.append(i*5+j);
      }
      lst.append(list);
  }
}


QVariant Model::headerData(int section,
                           Qt::Orientation orientation,
                           int role ) const
{
   if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
   {
       switch(section)
       {
       case 0: return "First";
       case 1: return "second";
       case 2: return "third";
       case 3: return "fourth";
       case 4: return "fifth";
       default:return QVariant();
       }
   }
   return QVariant();
}



int Model::rowCount(const QModelIndex &parent) const
{
    return lst.count();
}

int Model::columnCount(const QModelIndex &parent) const
{

    return lst.isEmpty()?0:lst.first().count();
}

QVariant Model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() >= lst.count()){
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
       return lst.at(index.row()).at(index.column());
    }

     return QVariant();

}



