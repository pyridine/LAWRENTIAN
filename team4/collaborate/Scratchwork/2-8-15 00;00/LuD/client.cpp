#include "client.h"
#include <iostream>
#include "remotedbconnection.h"

using namespace std;

Client::Client(){
    cout << "Hi, I am Client." << endl;
    RemoteDBConnection acon;
    connection = &acon;
}

bool Client::connect(){
    return connection->Connect();
}

QSqlQuery* Client::execute(string s)
{
    cout << "Executing <" << s << ">." << endl;
    return connection->execute(s);
}
QSqlQuery* Client::execute(QSqlQuery* q){
    cout << "Executing <" << q->lastQuery().toStdString() << ">." << endl;
    QSqlQuery result = *(connection->execute(q)); /*SEGFAULT?!?!?!?!*/
    QSqlQuery* resultp = &result;
    cout << resultp->lastError().text().toStdString() << endl;
    return resultp;
}

Client::~Client()
{

}

