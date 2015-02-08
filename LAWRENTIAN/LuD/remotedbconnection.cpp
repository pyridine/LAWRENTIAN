#include "remotedbconnection.h"
#include <QObject>
#include <iostream>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlquery.h>
#include <qvariant.h>
#include <string>

//This tutorial is extremely helpful: http://www.informit.com/articles/article.aspx?p=1405550


using namespace std;

RemoteDBConnection::RemoteDBConnection(){
    cout << "Hi, I am the Remote DB Connection." << endl;
}

RemoteDBConnection::~RemoteDBConnection(){
    database->removeDatabase(QString::fromStdString("lawrentian"));
    delete(&database);}

bool RemoteDBConnection::Connect()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    database = &db;
    database->setHostName("143.44.10.35");
    database->setDatabaseName("lawrentian");
    database->setUserName("dev");
    database->setPassword("dev");
    if (!database->open()) {
        cout << "Database Error: " << database->lastError().text().toStdString() << endl;
        return false;
    } else{
        cout << "Connection established :D" << endl;
        return true;
    }
}
void RemoteDBConnection::sampleQuery(){
    QSqlQuery query;
    cout << "Executing: ''SELECT * FROM employee''......." << endl;
    query.exec("SELECT * FROM employee");
    while (query.next()) {
        cout <<
                "luid: " << query.value(0).toString().toStdString() << endl <<
                "name: " << query.value(1).toString().toStdString() << endl <<
                "title: " << query.value(2).toString().toStdString() << endl <<
                "phone: " << query.value(3).toString().toStdString() << endl <<
                "email: " << query.value(4).toString().toStdString() << endl <<
                "username: " << query.value(5).toString().toStdString() << endl <<
                "password: " << query.value(6).toString().toStdString() << endl;
    }
}
QSqlQuery* RemoteDBConnection::execute(string s){
    QSqlQuery* query = new QSqlQuery(); //Without the pointer-new, you'd get a segfault!!

    QString queryString = QString::fromStdString(s);
    query->exec(queryString);
    return query;
}
bool RemoteDBConnection::execute(QSqlQuery* s){

    bool resultValue = s->exec();

    return resultValue;
}
