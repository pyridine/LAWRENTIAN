#include "profilewidgetdbc.h"

#include <QtSql>
#include <qvariant.h>
#include <iostream>

ProfileWidgetDBC::ProfileWidgetDBC(Client *c):DatabaseController(c)
{

}

void ProfileWidgetDBC::setCurrentIssueDate(QDate issueDate)
{
    QString issueDateString = issueDate.toString("yyyy-MM-dd");

    const string SET_ISSUE_DATE = "INSERT INTO issue_archive (issueDate) "
                                  "VALUES (:issueDate) "
                                  "ON DUPLICATE KEY UPDATE issueDate=:issueDate";

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(SET_ISSUE_DATE));
    query->bindValue(":issueDate", issueDateString);


    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        return;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }

}

QDate ProfileWidgetDBC::collectLatestIssueDate()
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

string ProfileWidgetDBC::collectArticleSection(int articleId){
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
        return NULL;
    }
}

string ProfileWidgetDBC::collectArticleTitle(int articleId){
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
        return NULL;
    }
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
        return NULL;
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
        return NULL;
    }
}

vector<int> ProfileWidgetDBC::collectPotentialProbationApprovals(QDate currentDate)
{
    QDate possibleApprovalDate = currentDate.addDays(-21);
    QString possibleApprovalDateString = possibleApprovalDate.toString(df::dbFormat);

    const string GET_PROBATION_APPROVALS = "SELECT DISTINCT luid FROM lawrentian.employee "
                                           "INNER JOIN lawrentian.writer_timesheet "
                                           "ON lawrentian.employee.luid = lawrentian.writer_timesheet.idwriter "
                                           "WHERE employee.probationDate <= :probationDate";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_PROBATION_APPROVALS));
    query->bindValue(":probationDate", possibleApprovalDateString);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<int> ids;

    if(!err.isValid()){
        while(result->next()){
            string approvedPerson = result->value(0).toString().toStdString();
            int approvedPersonInt = stoi(approvedPerson);
            ids.push_back(approvedPersonInt);
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return ids;
}


string ProfileWidgetDBC::collectProbationApproval(QDate currentDate, int luid)
{
    QDate possibleApprovalDate = currentDate.addDays(-21);
    QString possibleApprovalDateString = possibleApprovalDate.toString(df::dbFormat);
    int min = 3;

    const string GET_PROBATION_APPROVALS = "SELECT name, SUM(articles_ontime) FROM lawrentian.employee INNER JOIN lawrentian.writer_timesheet ON lawrentian.employee.luid = lawrentian.writer_timesheet.idwriter WHERE (luid=:luid) HAVING SUM(articles_ontime)>=3";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_PROBATION_APPROVALS));
    query->bindValue(":probationDate", possibleApprovalDateString);
    query->bindValue(":luid", luid);
    query->bindValue(":min", min);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

   string name;

    if(!err.isValid()){
        while(result->next()){
            name = result->value(0).toString().toStdString();
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return name;
}

vector<string> ProfileWidgetDBC::collectRegistrationApprovals()
{
    int unapproved = 0;

    const string GET_UNAPPROVED = "SELECT name FROM lawrentian.employee WHERE approved =:unapproved";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_UNAPPROVED));
    query->bindValue(":unapproved", unapproved);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<string> names;

    if(!err.isValid()){
        while(result->next()){
            string unapprovedPerson = result->value(0).toString().toStdString();
            names.push_back(unapprovedPerson);
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return names;
}

vector<int> ProfileWidgetDBC::collectArticleIdForTimesheet(QDate currentDate, int writerId)
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

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return articleIds;
}

vector<int> ProfileWidgetDBC::collectWriterForTimesheet(QDate currentDate)
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

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return writerIds;
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

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return count;
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

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return count;
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

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return count;
}

void ProfileWidgetDBC::setHoursWorked(int luid, QDate issueDate, int hoursWorked)
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

int ProfileWidgetDBC::getHoursWorked(int luid, QDate issueDate)
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


ProfileWidgetDBC::~ProfileWidgetDBC()
{

}

