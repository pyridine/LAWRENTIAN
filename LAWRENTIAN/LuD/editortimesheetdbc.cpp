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

    int hours = 0;

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

vector<vector<string>>* EditorTimesheetDBC::getTimesheet(QDate issueDate){
    int NUMBEROFCOLUMNS = 3;

    QString issueDateString = issueDate.toString("yyyy-MM-dd");

    const string GET_TIMESHEET = "SELECT name, hours, issueDate "
                                 "FROM lawrentian.editor_timesheet "
                                 "INNER JOIN lawrentian.employee "
                                 "ON editor_timesheet.luid = employee.luid "
                                 "WHERE editor_timesheet.issueDate =:issueDate";

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_TIMESHEET));
    query->bindValue(":issueDate", issueDateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<vector<string>>* matrix = new vector<vector<string>>();

    while(result->next()){
        vector<string>* nextRow = new vector<string>();
        for(int i = 0; i < NUMBEROFCOLUMNS; i++){
                nextRow->push_back(result->value(i).toString().toStdString());
        }
        matrix->push_back(*nextRow);
    }
    return matrix;
}

vector<int> EditorTimesheetDBC::collectEditorForTimesheet(QDate currentDate)
{
    QString currentDateString = currentDate.toString("yyyy-MM-dd");

    const string GET_WRITERS = "SELECT luid FROM lawrentian.editor_timesheet "
                               "WHERE editor_timesheet.issueDate =:currentDate";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_WRITERS));
    query->bindValue(":currentDate", currentDateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<int> editorIds;

    if(!err.isValid()){
        while(result->next()){
            string editor = result->value(0).toString().toStdString();
            int editorInt = stoi(editor);
            editorIds.push_back(editorInt);
        }
        return editorIds;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}


EditorTimesheetDBC::~EditorTimesheetDBC()
{

}

