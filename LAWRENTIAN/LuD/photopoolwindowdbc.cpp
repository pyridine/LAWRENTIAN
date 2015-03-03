#include "photopoolwindowdbc.h"
#include <QStringList>
#include <iostream>


PhotoPoolWindowDBC::PhotoPoolWindowDBC(Client *c):DatabaseController(c)
{
}

//PhotoPoolWindowDBC::PhotoPoolWindowDBC():DatabaseController(c)
//{

//}

PhotoPoolWindowDBC::~PhotoPoolWindowDBC()
{

}

QStringList PhotoPoolWindowDBC::getArtsFromSec(int sec, const QString& fromIssueDate, const QString& toIssueDate)
{
    using namespace std;
    QStringList sec_arts;
    QSqlQuery* query = new QSqlQuery();

    query->prepare("SELECT title,issueDate FROM lawrentian.currentissue_article WHERE section = :sec ORDER BY title");
    query->bindValue(":sec",sec);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid())
    {
        while(result->next())
        {
            QString title = result->value("title").toString();
            QString dbIssueDate = QDate::fromString(result->value("issueDate").toString(),"yyyy-MM-dd").toString("dd MMM, yyyy");

            QDate dbDate = QDate::fromString(dbIssueDate,"dd MMM, yyyy");
            QDate fromDate = QDate::fromString(fromIssueDate,"dd MMM, yyyy");
            QDate toDate = QDate::fromString(toIssueDate,"dd MMM, yyyy");

            if(dbDate >= fromDate && dbDate <= toDate)
                sec_arts.push_back(title);
        }

    }
    else
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;

    return sec_arts;

}

QStringList PhotoPoolWindowDBC::getArtsFromSec(int sec)
{
    using namespace std;

    QStringList sec_arts;
    QSqlQuery* query = new QSqlQuery();

    query->prepare("SELECT title FROM lawrentian.currentissue_article WHERE section = :sec ORDER BY title");
    query->bindValue(":sec",sec);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid())
    {
        while(result->next())
            sec_arts.push_back(result->value("title").toString());
    }
    else
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;

    return sec_arts;

}

QStringList PhotoPoolWindowDBC::getIssueDates()
{
    using namespace std;

    QStringList all_issueDates;
    QSqlQuery* query = new QSqlQuery();

    query->prepare("SELECT issueDate FROM lawrentian.currentissue_article ORDER BY issueDate");

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid())
    {
        QString prevDate;
        while(result->next())
        {
            QString date = result->value("issueDate").toString();
            QString formattedDate = QDate::fromString(date,"yyyy-MM-dd").toString("dd MMM, yyyy");
            if(prevDate.compare(formattedDate))
                all_issueDates.push_back(formattedDate);
            prevDate = formattedDate;
        }
    }
    else
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;

    return all_issueDates;
}

string PhotoPoolWindowDBC::getIssueDateOfArt(QString title)
{
    QSqlQuery* query = new QSqlQuery();

    query->prepare("SELECT issueDate FROM lawrentian.currentissue_article WHERE title = :title");
    query->bindValue(":title", title);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid())
    {
        while(result->next())
            return result->value("issueDate").toString().toStdString();
    }
    else
        std::cout << "!SQL ERROR: " << result->lastError().text().toStdString() << std::endl;

    return "";

}

std::vector<PhotoPoolWindowDBC::Sec_t> PhotoPoolWindowDBC::getSections()
{
    using namespace std;

    vector<Sec_t> all_sections;
    QSqlQuery* query = new QSqlQuery();

    query->prepare("SELECT idsection,sectionName FROM lawrentian.section");

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid())
    {
        while(result->next())
        {
            int id = result->value("idsection").toInt();
            string sec = result->value("sectionName").toString().toStdString();
            all_sections.push_back(Sec_t(id, sec));
        }
    }
    else
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;

    return all_sections;

}



