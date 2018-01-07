#include "dbinterface.h"
#include <QDebug>


DbInterface::DbInterface()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("settings.db");
    if(!db.open()){
        qDebug()<<"error";
        return;
    }

    QStringList lst = db.tables();
    if(!db.tables().contains(QString("header")))
    {
        QSqlQuery q(db);
        bool pr = q.prepare("CREATE TABLE header (default_order	TEXT, hided_columns TEXT)");
        if(!pr)qDebug()<<q.lastError();
        pr = q.exec();
        if(!pr)qDebug()<<q.lastError();
        pr = q.prepare("INSERT INTO header (default_order	, hided_columns ) VALUES(\"\",\"\")");
        if(!pr)qDebug()<<q.lastError();
        pr = q.exec();
        if(!pr)qDebug()<<q.lastError();
    }
}
QString DbInterface::getOrder() const
{
    QSqlQuery q(db);
    bool pr = q.prepare("SELECT default_order FROM header");
    if(!pr)qDebug()<<q.lastError();
    pr = q.exec();
    q.first();
    QString res = q.value(0).toString();

    return res;
}
void DbInterface::setOrder(QString str)
{
    QSqlQuery q(db);
    q.clear();
    bool pr = q.prepare("UPDATE header SET default_order = ?");
    if(!pr)qDebug()<<q.lastError();
    q.addBindValue(str);
    pr = q.exec();
    if(!pr)qDebug()<<q.lastError();

}



QString DbInterface::getHidedColumns() const
{
    QSqlQuery q(db);
    bool pr = q.prepare("SELECT hided_columns FROM header");
    if(!pr)qDebug()<<q.lastError();
    pr = q.exec();
    q.first();
    QString res = q.value(0).toString();

    return res;

}
void DbInterface::setHidedColumns(QString str)
{
    QSqlQuery q(db);
    q.clear();
    bool pr = q.prepare("UPDATE header SET hided_columns = ?");
    if(!pr)qDebug()<<q.lastError();
    q.addBindValue(str);
    pr = q.exec();
    if(!pr)qDebug()<<q.lastError();

}

