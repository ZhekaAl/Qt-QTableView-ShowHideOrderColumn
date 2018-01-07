#ifndef VIEW_H
#define VIEW_H


#include "dbinterface.h"

#include <QTableView>

class View:public QTableView
{
    Q_OBJECT
public:
    View(QWidget *parent = 0);
    ~View(){}

    void restoreOrder();
    void restoreDefaultHidedColumns();


private slots:
    void showHeaderMenu(QPoint p);
    void slotHideColumn();
    void showHidedColumn();
    void slotMoveLast();
    void slotMoveFirst();
    void slotRestoreDefault();
    void saveCurrentSettings();



private:


    QHeaderView* header;
    QAction* hideAction
            ,*moveLast
             ,*moveFirst;

    QList<int> currentHidedColumns,
               defaultHidedColumns ;
    void loadHideColumns();
    void saveCurrentHidedColumns();

    QList<int> order;
    void loadOrder();
    void saveCurrentOrder();

    DbInterface dbInterface;




};

#endif // VIEW_H
