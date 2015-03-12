#include "writertimesheetdbc.h"

#include <iostream>

WriterTimesheetDBC::WriterTimesheetDBC(Client *c):DatabaseController(c)
{

}

QDate WriterTimesheetDBC::collectLatestIssueDate()
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

vector<QDate> WriterTimesheetDBC::getTimesheetDateList()
{
    const string GET_ISSUE_DATES = "SELECT DISTINCT writer_timesheet.issueDate "
                                   "FROM lawrentian.writer_timesheet "
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

bool WriterTimesheetDBC::getFrozen(QDate date)
{
    QString dateString = date.toString(df::dbFormat);
    const string GET_ISSUE_DATES = "SELECT frozen FROM lawrentian.writer_timesheet WHERE issueDate =:issueDate";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_ISSUE_DATES));
    query->bindValue(":issueDate", dateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    bool frozen;

    if(!err.isValid()){
        while(result->next()){
            QString frozenString = result->value(0).toString();
            int frozenChar = frozenString.toInt();
            if(frozenChar == 0){
                frozen = false;
            } else {
                frozen = true;
            }
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return frozen;
}

void WriterTimesheetDBC::setFrozen(QDate date)
{
    QString dateString = date.toString(df::dbFormat);
    const string SET_FROZEN = "UPDATE lawrentian.writer_timesheet SET frozen=1 WHERE issueDate = :issueDate";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(SET_FROZEN));
    query->bindValue(":issueDate", dateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();


    if(!err.isValid()){

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
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
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return sectionName;
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
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return articleName;
}

vector<int> WriterTimesheetDBC::collectArticleIdForTimesheet(QDate currentDate, int writerId)
{
    QString currentDateString = currentDate.toString(df::dbFormat);

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
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return articleIds;
}

vector<int> WriterTimesheetDBC::collectWriterForTimesheet(QDate currentDate)
{
    QString currentDateString = currentDate.toString(df::dbFormat);

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
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return writerIds;
}

void WriterTimesheetDBC::generateWriterTimesheet(int writerId, int articlesOnTime, int articlesLate, QDate issueDate)
{
    QString issueDateString = issueDate.toString(df::dbFormat);

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

void WriterTimesheetDBC::updateWriterTimesheet(int writerId, int articlesOnTime, int articlesLate, QDate issueDate)
{

   QString issueDateString = issueDate.toString(df::dbFormat);

   const string UPDATE_WRITER_TIMESHEET = "INSERT INTO lawrentian.writer_timesheet (idwriter, articles_ontime, articles_late, issueDate) "
                                        "VALUES (:idwriter, :articles_ontime, :articles_late, :issueDate) "
                                        "ON DUPLICATE KEY UPDATE idwriter =:idwriter, articles_ontime =:articles_ontime, articles_late =:articles_late, issueDate =:issueDate";

   QSqlQuery* query = new QSqlQuery();
   query->prepare(QString::fromStdString(UPDATE_WRITER_TIMESHEET));
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
    QString issueDateString = issueDate.toString(df::dbFormat);

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
    QString issueDateString = issueDate.toString(df::dbFormat);

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
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return count;
}

int WriterTimesheetDBC::collectArticlesLate(int writer, QDate issueDate)
{
    QString issueDateString = issueDate.toString(df::dbFormat);

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
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return count;
}

// Returns number of entries for the issue date
int WriterTimesheetDBC::writerTimesheetExists(QDate issueDate)
{
    QString issueDateString = issueDate.toString(df::dbFormat);

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
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return count;
}

vector<vector<string>>* WriterTimesheetDBC::getTimesheet(QDate issueDate){
    int NUMBEROFCOLUMNS = 4;

    QString issueDateString = issueDate.toString(df::dbFormat);

    const string GET_TIMESHEET = "SELECT name, articles_ontime, articles_late, issueDate "
                                 "FROM lawrentian.writer_timesheet "
                                 "INNER JOIN lawrentian.employee "
                                 "ON writer_timesheet.idwriter = employee.luid "
                                 "WHERE writer_timesheet.issueDate =:issueDate";

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

QDate WriterTimesheetDBC::collectLatestTimesheetDate()
{
    const string GET_ARTICLESONTIME = "SELECT issueDate FROM lawrentian.writer_timesheet "
                                      "WHERE writer_timesheet.issueDate IN (SELECT max(issueDate) FROM lawrentian.writer_timesheet)";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_ARTICLESONTIME));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    QDate latestDate;

    if(!err.isValid()){
        // Checks if issue already exists
        while(result->next()){
            QString date = result->value(0).toString();
            latestDate = QDate::fromString(date, df::dbFormat);
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return latestDate;
}

int WriterTimesheetDBC::getLuidForName(string name)
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

void WriterTimesheetDBC::setArticleSubmissionsForLuid(int luid, int articlesOnTime, int articlesLate)
{
    const string SET_FROZEN = "UPDATE lawrentian.writer_timesheet "
                              "SET articles_ontime=:articlesOnTime, articles_late=:articlesLate WHERE idwriter = :luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(SET_FROZEN));
    query->bindValue(":articlesOnTime", articlesOnTime);
    query->bindValue(":articlesLate", articlesLate);
    query->bindValue(":luid",luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();


    if(!err.isValid()){

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}


WriterTimesheetDBC::~WriterTimesheetDBC()
{

}

