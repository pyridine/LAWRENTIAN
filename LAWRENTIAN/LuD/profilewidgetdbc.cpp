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

vector<string> ProfileWidgetDBC::collectProbationApprovals(QDate currentDate)
{
    QDate possibleApprovalDate = currentDate.addDays(-21);
    QString possibleApprovalDateString = possibleApprovalDate.toString("yyyy-MM-dd");

    const string GET_PROBATION_APPROVALS = "SELECT name FROM lawrentian.employee "
                                           "INNER JOIN lawrentian.writer_timesheet "
                                           "ON lawrentian.employee.luid = lawrentian.writer_timesheet.idwriter "
                                           "WHERE employee.probationDate <= :probationDate "
                                           "AND writer_timesheet.articles_ontime >= 3";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_PROBATION_APPROVALS));
    query->bindValue(":probationDate", possibleApprovalDateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<string> names;

    if(!err.isValid()){
        while(result->next()){
            string approvedPerson = result->value(0).toString().toStdString();
            names.push_back(approvedPerson);
        }
        return names;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

ProfileWidgetDBC::~ProfileWidgetDBC()
{

}

