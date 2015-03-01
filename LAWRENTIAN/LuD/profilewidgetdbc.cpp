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

vector<int> ProfileWidgetDBC::collectWriterForTimesheet(QDate currentDate)
{
    QString currentDateString = currentDate.toString("yyyy-MM-dd");

    const string GET_WRITERS = "SELECT writer FROM lawrentian.currentissue_article "
                                           "WHERE currentissue_article.issueDate =:currentDate";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_WRITERS));
    query->bindValue(":currentDate", currentDateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<int> writerIds;

    if(!err.isValid()){
        while(result->next()){
            string writer = result->value(0).toString().toStdString();
            int writerInt = stoi(writer);
            writerIds.push_back(writerInt);
        }
        return writerIds;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

void ProfileWidgetDBC::generateWriterTimesheet(int writerId, int articlesOnTime, int articlesLate, QDate issueDate)
{
    QString issueDateString = issueDate.toString("yyyy-MM-dd");

    const string GENERATE_WRITER_TIMESHEET = "INSERT INTO lawrentian.writer_timesheet (idwriter, articles_ontime, articles_late, issueDate) "
                                             "VALUES (:idwriter, :articles_ontime, :articles_late, :issueDate)";

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GENERATE_WRITER_TIMESHEET));
    query->bindValue(":idwriter", writerId);
    query->bindValue(":articles_ontime", articlesOnTime);
    query->bindValue(":articles_late", articlesLate);
    query->bindValue(":issueDate", issueDateString);


    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        return;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

void ProfileWidgetDBC::deleteWriterTimesheetRecords(QDate issueDate)
{
    QString issueDateString = issueDate.toString("yyyy-MM-dd");

    const string DELETE_RECORDS = "DELETE FROM lawrentian.writer_timesheet WHERE writer_timesheet.issueDate =:issueDate";

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(DELETE_RECORDS));
    query->bindValue(":issueDate", issueDateString);


    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        return;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

int ProfileWidgetDBC::collectArticlesOnTime(int writer, QDate issueDate)
{
    QString issueDateString = issueDate.toString("yyyy-MM-dd");

    const string GET_ARTICLESONTIME = "SELECT idarticle FROM lawrentian.currentissue_article "
                                           "WHERE currentissue_article.writer =:writer AND issueDate =:issueDate";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_ARTICLESONTIME));
    query->bindValue(":writer", writer);
    query->bindValue(":issueDate", issueDateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    int count = 0;

    if(!err.isValid()){
        while(result->next()){
            count++;
        }
        return count;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

int ProfileWidgetDBC::collectArticlesLate(int writer, QDate issueDate)
{
    QString issueDateString = issueDate.toString("yyyy-MM-dd");

    const string GET_ARTICLESLATE = "SELECT idarticle FROM lawrentian.currentissue_article "
                                           "WHERE currentissue_article.writer =:writer AND issueDate =:issueDate";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_ARTICLESLATE));
    query->bindValue(":writer", writer);
    query->bindValue(":issueDate", issueDateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    int count = 0;

    if(!err.isValid()){
        while(result->next()){
            count++;
        }
        return count;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

// Returns number of entries for the issue date
int ProfileWidgetDBC::writerTimesheetExists(QDate issueDate)
{
    QString issueDateString = issueDate.toString("yyyy-MM-dd");

    const string GET_ARTICLESONTIME = "SELECT issueDate FROM lawrentian.writer_timesheet WHERE writer_timesheet.issueDate =:issueDate";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_ARTICLESONTIME));
    query->bindValue(":issueDate", issueDateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    int count = 0;

    if(!err.isValid()){
        // Checks if issue already exists
        while(result->next()){
            count++;
        }
        return count;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}


ProfileWidgetDBC::~ProfileWidgetDBC()
{

}

