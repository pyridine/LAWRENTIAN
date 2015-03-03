#include "databasecontroller.h"
#include "client.h"
#include <QtSql>
#include <string>
#include <iostream>
#include <qvariant.h>
#include <QTableWidgetItem>


DatabaseController::DatabaseController(Client* c){
    client = c;
}

Client* DatabaseController::getClient(){
    return client;
}

void DatabaseController::executeSQLString(QString sql){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(sql);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(err.isValid()) cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;

    return;
}

void DatabaseController::executeSQLString_Args(string sql, vector<string> *bindNames, vector<QVariant> *bindList){
    if(bindNames->size() != bindList->size()){
        cout << "ERROR: BINDLIST AND BINDNAMES ARE NOT THE SAME SIZE! SQL NOT EXECUTED." << endl;
        return;
    }

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(sql));

    vector<string>::iterator binder = bindNames->begin();
    vector<QVariant>::iterator binded = bindList->begin();
    while(binder != bindNames->end()){
        QString bindName = QString::fromStdString(*binder);
        QVariant bindVal = *binded;
        query->bindValue(bindName,bindVal);
    }

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(err.isValid()) cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;

    return;
}


string DatabaseController::translateLocation(int locID){
    string transLoc = "SELECT name FROM lawrentian.location WHERE idlocation = :narm";

    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(transLoc));

    query->bindValue(":narm",locID);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            return result->value(0).toString().toStdString();
        } else{
            return "Error";
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return "Error";
    }
}
vector<int>* DatabaseController::execute_int_for_intvect(string sql, string argname, int arg){
    QSqlQuery* query = new QSqlQuery();
    vector<int>* numz = new vector<int>();

    query->prepare(QString::fromStdString(sql));

    query->bindValue(QString::fromStdString(argname),QVariant(arg));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            numz->push_back(result->value(0).toInt());
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return numz;
}

string DatabaseController::translatePermission(int permID){
    string transLoc = "SELECT description FROM lawrentian.permissiontokens WHERE idToken = :id";

    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(transLoc));

    query->bindValue(":id",permID);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            return result->value(0).toString().toStdString();
        } else{
            return "Error";
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return "Error";
    }
}
string DatabaseController::translateTitle(int titleID){
    string transLoc = "SELECT titleName FROM lawrentian.titledefinitions WHERE idTitle = :id";

    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(transLoc));

    query->bindValue(":id",titleID);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            return result->value(0).toString().toStdString();
        } else{
            return "Error";
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return "Error";
    }
}

string DatabaseController::translateSection(int secID){
    string transLoc = "SELECT sectionName FROM lawrentian.section WHERE idsection = :id";

    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(transLoc));

    query->bindValue(":id",secID);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            return result->value(0).toString().toStdString();
        } else{
            return "Error";
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return false;
    }
}
string DatabaseController::translateRoute(int rID){
    string transLoc = "SELECT routename FROM lawrentian.routenames WHERE routeID = :rID";

    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(transLoc));

    query->bindValue(":rID",rID);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            return result->value(0).toString().toStdString();
        } else{
            return "Route Name";
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return "Error";
    }
}

vector<int> *DatabaseController::execute_null_for_intvect(string sql){
    QSqlQuery* query = new QSqlQuery();
    vector<int>* numz = new vector<int>();

    query->prepare(QString::fromStdString(sql));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            numz->push_back(result->value(0).toInt());
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return numz;
}
