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
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return false;
    }
    return false;
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
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return false;
    }
    return false;
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
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return false;
    }
    return false;
}

string DatabaseController::translateSection(int secId){
    string transLoc = "SELECT sectionName FROM lawrentian.section WHERE idsection = :id";

    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(transLoc));

    query->bindValue(":id",secId);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            return result->value(0).toString().toStdString();
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return false;
    }
    return false;
}
