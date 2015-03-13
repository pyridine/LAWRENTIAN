#ifndef REMOTEDBCONNECTION_H
#define REMOTEDBCONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/qsql.h>
#include <qtsql/qsqlquery.h>
#include <string>

using namespace std;

class RemoteDBConnection
{
public:
    RemoteDBConnection();
    bool Connect();
    void sampleQuery();
    ~RemoteDBConnection();
    QSqlQuery* execute(string s);
    QSqlQuery* execute(QSqlQuery* q);
private:
    QSqlDatabase* database;
};

#endif // REMOTEDBCONNECTION_H
