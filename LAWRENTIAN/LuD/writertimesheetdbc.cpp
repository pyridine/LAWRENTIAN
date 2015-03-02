#include "writertimesheetdbc.h"

#include <iostream>

WriterTimesheetDBC::WriterTimesheetDBC(Client *c):DatabaseController(c)
{

}

vector<int> WriterTimesheetDBC::collectWriterForTimesheet(QDate currentDate)
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

void WriterTimesheetDBC::generateWriterTimesheet(int writerId, int articlesOnTime, int articlesLate, QDate issueDate)
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

void WriterTimesheetDBC::deleteWriterTimesheetRecords(QDate issueDate)
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

int WriterTimesheetDBC::collectArticlesOnTime(int writer, QDate issueDate)
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

int WriterTimesheetDBC::collectArticlesLate(int writer, QDate issueDate)
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
int WriterTimesheetDBC::writerTimesheetExists(QDate issueDate)
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

WriterTimesheetDBC::~WriterTimesheetDBC()
{

}

