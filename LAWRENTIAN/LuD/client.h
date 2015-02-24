#ifndef CLIENT_H
#define CLIENT_H
#include "remotedbconnection.h"
#include <QtSql>

class Client
{
public:
    Client();
    bool connect();
    QSqlQuery* execute(string s) const;
    QSqlQuery* execute(QSqlQuery* q) const;
    void sampleQuery();
    ~Client();
private:
    RemoteDBConnection* connection;
};

#endif // CLIENT_H
