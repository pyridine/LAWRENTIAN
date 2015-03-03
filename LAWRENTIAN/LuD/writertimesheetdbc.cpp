#include "writertimesheetdbc.h"

#include <iostream>

WriterTimesheetDBC::WriterTimesheetDBC(Client *c):DatabaseController(c)
{

}

string WriterTimesheetDBC::collectArticleSection(int articleId){
    const string GET_NAME = "SELECT lawrentian.section.sectionName "
                            "FROM lawrentian.section "
                            "INNER JOIN lawrentian.currentissue_article "
                            "ON lawrentian.currentissue_article.section = lawrentian.section.idsection "
                            "WHERE lawrentian.currentissue_article.idarticle = :idarticle";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_NAME));
    query->bindValue(":idarticle", articleId);

    string sectionName;

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            sectionName = result->value(0).toString().toStdString();
        }
        return sectionName;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

string WriterTimesheetDBC::collectArticleTitle(int articleId){
    const string GET_NAME = "SELECT title FROM lawrentian.currentissue_article WHERE idarticle =:articleId";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_NAME));
    query->bindValue(":articleId", articleId);

    string articleName;

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            articleName = result->value(0).toString().toStdString();
        }
        return articleName;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

vector<int> WriterTimesheetDBC::collectArticleIdForTimesheet(QDate currentDate, int writerId)
{
    QString currentDateString = currentDate.toString("yyyy-MM-dd");

    const string GET_ARTICLEID = "SELECT idarticle FROM lawrentian.currentissue_article "
                                           "WHERE currentissue_article.issueDate =:currentDate AND currentissue_article.writer =:writerId";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_ARTICLEID));
    query->bindValue(":currentDate", currentDateString);
    query->bindValue(":writerId", writerId);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<int> articleIds;

    if(!err.isValid()){
        while(result->next()){
            string id = result->value(0).toString().toStdString();
            int idInt = stoi(id);
            articleIds.push_back(idInt);
        }
        return articleIds;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

vector<int> WriterTimesheetDBC::collectWriterForTimesheet(QDate currentDate)
{
    QString currentDateString = currentDate.toString("yyyy-MM-dd");

    const string GET_WRITERS = "SELECT DISTINCT writer FROM lawrentian.currentissue_article "
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

