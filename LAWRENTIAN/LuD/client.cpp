#include "client.h"
#include <iostream>
#include "remotedbconnection.h"

using namespace std;

Client::Client(){
    cout << "Hi, I am Client." << endl;
    RemoteDBConnection acon;
    cout << "made RWDBC." << endl;
    connection = &acon;
    cout << "done!" << endl;
}

bool Client::connect(){
    return connection->Connect();
}

QSqlQuery* Client::execute(string s) const
{
    QSqlQuery* returned = connection->execute(s);
    cout << returned->lastError().text().toStdString() << endl;
    return returned;
}
QSqlQuery* Client::execute(QSqlQuery* q) const
{
    connection->execute(q);
    cout << q->executedQuery().toStdString() << endl;
    cout << q->lastError().text().toStdString() << endl;
    return q;
}

Client::~Client()
{

}

