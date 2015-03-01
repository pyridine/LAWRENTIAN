#include "editortimesheetdbc.h"

#include <iostream>

EditorTimesheetDBC::EditorTimesheetDBC(Client *c):DatabaseController(c)
{

}

void EditorTimesheetDBC::setHoursWorked(int luid, QDate issueDate, int hoursWorked)
{
    QString issueDateString = issueDate.toString("yyyy-MM-dd");

    const string SET_HOURS_WORKED = "INSERT INTO lawrentian.editor_timesheet (luid, hours, issueDate) "
                                    "VALUES (:luid, :hours, :issueDate) "
                                    "ON DUPLICATE KEY UPDATE luid =:luid, hours =:hours, issueDate =:issueDate";

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(SET_HOURS_WORKED));
    query->bindValue(":luid", luid);
    query->bindValue(":hours", hoursWorked);
    query->bindValue(":issueDate", issueDateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        return;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

int EditorTimesheetDBC::getHoursWorked(int luid, QDate issueDate)
{
    QString issueDateString = issueDate.toString("yyyy-MM-dd");

    const string GET_WRITERS = "SELECT hours FROM lawrentian.editor_timesheet "
                                           "WHERE editor_timesheet.luid =:luid AND editor_timesheet.issueDate =:issueDate";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_WRITERS));
    query->bindValue(":issueDate", issueDateString);
    query->bindValue(":luid", luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    int hours;

    if(!err.isValid()){
        while(result->next()){
            string hoursString = result->value(0).toString().toStdString();
            hours = stoi(hoursString);
        }
        return hours;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

EditorTimesheetDBC::~EditorTimesheetDBC()
{

}

