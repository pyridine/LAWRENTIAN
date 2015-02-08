#include "client.h"
#include <iostream>
#include "remotedbconnection.h"

using namespace std;

Client::Client(){
    cout << "Hi, I am Client." << endl;
    RemoteDBConnection acon;
    this->connection = &acon;
}

bool Client::connect(){
    return connection->Connect();
}

QSqlQuery* Client::execute(string s) const
{
    cout << "Executing <" << s << ">." << endl;
    return connection->execute(s);


}
QSqlQuery* Client::execute(QSqlQuery* q) const
{
    cout << "Executing <" << q->lastQuery().toStdString() << ">." << endl;
    connection->execute(q); /*SEGFAULT?!?!?!?! "THIS" PTR IS NULL!?!?!?*/
    cout << q->lastError().text().toStdString() << endl;
    return q;
}

Client::~Client()
{

}

