#include "editortimesheetdbc.h"

#include <iostream>

EditorTimesheetDBC::EditorTimesheetDBC(Client *c):DatabaseController(c)
{

}

QDate EditorTimesheetDBC::collectLatestIssueDate()
{
    const string GET_LATEST_ISSUE_DATE = "SELECT issueDate FROM lawrentian.issue_archive WHERE issue_archive.issueDate IN (SELECT max(issueDate) FROM issue_archive)";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_LATEST_ISSUE_DATE));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    QDate latestDate;

    if(!err.isValid()){
        // Checks if issue already exists
        while(result->next()){
            QString date = result->value(0).toString();
            latestDate = QDate::fromString(date, "yyyy-MM-dd");
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return latestDate;
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

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return hours;
}

vector<QDate> EditorTimesheetDBC::getTimesheetDateList()
{
    const string GET_ISSUE_DATES = "SELECT DISTINCT editor_timesheet.issueDate "
                                   "FROM lawrentian.editor_timesheet "
                                   "ORDER BY issueDate DESC";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_ISSUE_DATES));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<QDate> issueDateList;

    if(!err.isValid()){
        while(result->next()){
            QString date = result->value(0).toString();
            QDate qDate = QDate::fromString(date, "yyyy-MM-dd");
            issueDateList.push_back(qDate);
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return issueDateList;
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

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;        
    }
    return editorIds;
}

int EditorTimesheetDBC::getLuidForName(string name)
{
    const string GET_LUID = "SELECT luid FROM lawrentian.employee WHERE name =:name";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_LUID));
    query->bindValue(":name", QString::fromStdString(name));

    int luid;

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            string luidString = result->value(0).toString().toStdString();
            luid = stoi(luidString);
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return luid;
}


EditorTimesheetDBC::~EditorTimesheetDBC()
{

}

