#include "client.h"
#include <iostream>
#include "remotedbconnection.h"

using namespace std;

Client::Client(){
    RemoteDBConnection* acon = new RemoteDBConnection();
    connection = acon;
}

bool Client::connect(){
    return connection->Connect();
}

void Client::sampleQuery(){
    connection->execute("sample");
}


QSqlQuery* Client::execute(string s) const
{
    QSqlQuery* returned = connection->execute(s);
    return returned;
}
QSqlQuery* Client::execute(QSqlQuery* q) const
{
    connection->execute(q);
    return q;
}

Client::~Client()
{

}

