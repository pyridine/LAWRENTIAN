#ifndef CLIENT_H
#define CLIENT_H
#include "remotedbconnection.h"
#include <QtSql>

class Client
{
public:
    Client();
    bool connect();
    QSqlQuery execute(string s);
    QSqlQuery execute(QSqlQuery &q);
    ~Client();
private:
    RemoteDBConnection *connection;
};

#endif // CLIENT_H
