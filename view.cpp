#include "view.h"
#include "dbinterface.h"

#include <QHeaderView>
#include<QMenu>
#include<QDebug>

View::View(QWidget *parent):QTableView(parent)
{
    header =   horizontalHeader();
    header->setSectionsMovable(true);
    header->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(header, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showHeaderMenu(const QPoint &)));

    hideAction = new QAction("Hide",this);
    connect(hideAction,SIGNAL(triggered(bool)),this,SLOT(slotHideColumn()));

    moveLast = new QAction("MoveLast",this);
    connect(moveLast,SIGNAL(triggered(bool)),this,SLOT(slotMoveLast()));
    moveFirst = new QAction("MoveFirst",this);
    connect(moveFirst,SIGNAL(triggered(bool)),this,SLOT(slotMoveFirst()));


    loadOrder();
    loadHideColumns();

}

void View::showHeaderMenu(QPoint p)
{
    QMenu menu;
    QPoint p2 = mapToGlobal(p);

    int logicIndex = header->logicalIndexAt(p);
    qDebug()<<"logInd"<<logicIndex;
    hideAction->setData(logicIndex);

    if(model()->columnCount()-currentHidedColumns.size()>1)
    {
        QString nameCurrent = model()->headerData(logicIndex, Qt::Horizontal).toString() ;
        hideAction->setText( "Hide "+nameCurrent);
        menu.addAction(hideAction);
    }

    menu.addAction(moveLast);
    moveLast->setData(logicIndex);

    menu.addAction(moveFirst);
    moveFirst->setData(logicIndex);


    for(int num : currentHidedColumns)
    {
        QString name = model()->headerData(num, Qt::Horizontal).toString() ;
        menu.addAction("Show "+name,this,SLOT(showHidedColumn()));
        menu.actions().last()->setData(num);
    }
    menu.addAction("Restore default settings",this,SLOT(slotRestoreDefault()));
    menu.addAction("Save current settings",this,SLOT(saveCurrentSettings()));
    menu.exec(p2);
}

void View::slotHideColumn()
{
    int colNum = hideAction->data().toInt();
    currentHidedColumns.append(colNum);
    hideColumn(colNum);
}

void View::slotMoveLast()
{
    int last = header->count()-1;
    int current = moveLast->data().toInt();
    int from = header->visualIndex(current);

    header->moveSection(from,last);
}

void View::slotMoveFirst()
{
    int current = moveFirst->data().toInt();
    int from = header->visualIndex(current);
    header->moveSection(from,0);
}

void View::showHidedColumn()
{
    QAction* act= (QAction*)sender();
    int ind = act->data().toInt();
    showColumn(ind);
    currentHidedColumns.removeOne(ind);

}

void View::slotRestoreDefault()
{
   restoreDefaultHidedColumns();
   restoreOrder();

}


void View::loadOrder()
{
  QString str = dbInterface.getOrder();
  QStringList lst = str.split(",");
  order.clear();
  for(QString s : lst)
      order.append(s.toInt());
}


void View::restoreDefaultHidedColumns()
{
    currentHidedColumns = defaultHidedColumns;

    for(int i=0;i<header->count();i++)
    {
        if(currentHidedColumns.contains(i))
        {
            hideColumn(i);
        }
        else
        {
            showColumn(i);
        }
    }
}

void View::restoreOrder()
{

    if(header->count() < order.count())
    {
        qDebug()<<"order Incorrect";
        return ;
    }

    for(int i=0; i<order.count(); i++)
    {
        int defPos = order.at(i);
        int realPos = header->visualIndex(i);

        if(realPos != defPos)
        {
            header->moveSection(realPos, defPos);
            i=0;
        }
    }
}


void View::saveCurrentOrder()
{
  QStringList currentOrder;
  for(int i=0; i<header->count();i++)
  {
      int visualPos = header->logicalIndex(i);
      currentOrder.append(QString::number(visualPos));

  }

  QString str = currentOrder.join(",");
  dbInterface.setOrder(str);

  order.clear();
  for(QString s : currentOrder)
      order.append(s.toInt());
}


void View::loadHideColumns()
{
    QString str = dbInterface.getHidedColumns();
    QStringList lst = str.split(",");
    defaultHidedColumns.clear();
    for(QString s : lst)
        defaultHidedColumns.append(s.toInt());

}
void View::saveCurrentHidedColumns(){

    defaultHidedColumns = currentHidedColumns;

    QStringList lst ;
    for(int i: defaultHidedColumns)
    {
           lst.append(QString::number(i));
    }
    QString str = lst.join(",");
    dbInterface.setHidedColumns(str);
}

void View::saveCurrentSettings()
{
    saveCurrentOrder();
    saveCurrentHidedColumns();
}
