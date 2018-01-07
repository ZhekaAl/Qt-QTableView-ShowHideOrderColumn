#ifndef DBINTERFACE_H
#define DBINTERFACE_H


#include <QtSql>
#include <QString>

class DbInterface
{
public:
    DbInterface();
    QString getOrder() const;
    void setOrder(QString );
    QString getHidedColumns() const;
    void setHidedColumns(QString);
private:
    QSqlDatabase db;
};

#endif // DBINTERFACE_H
