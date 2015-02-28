#include "profilewidgetdbc.h"

#include <QtSql>
#include <qvariant.h>
#include <iostream>

ProfileWidgetDBC::ProfileWidgetDBC(Client *c):DatabaseController(c)
{

}

string ProfileWidgetDBC::collectName(int luid){
    const string GET_NAME = "SELECT name FROM lawrentian.employee WHERE luid =:luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_NAME));
    query->bindValue(":luid", luid);

    string name;

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            name = result->value(0).toString().toStdString();
        }
        return name;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

string ProfileWidgetDBC::collectTitle(int luid)
{
    const string GET_TITLE = "SELECT lawrentian.titledefinitions.titleName "
                            "FROM lawrentian.titledefinitions "
                            "INNER JOIN lawrentian.employee "
                            "ON lawrentian.titledefinitions.idTitle = lawrentian.employee.title "
                            "WHERE lawrentian.employee.luid = :luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_TITLE));
    query->bindValue(":luid", luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    string title;

    if(!err.isValid()){
        while(result->next()){
            title = result->value(0).toString().toStdString();
        }
        return title;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

ProfileWidgetDBC::~ProfileWidgetDBC()
{

}

