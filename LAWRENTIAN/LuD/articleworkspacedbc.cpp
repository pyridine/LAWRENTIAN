#include "articleworkspacedbc.h"
#include <iostream>

namespace AWDBCCommands {
    const string GET_ARTICLE_BY_SECTION = "SELECT * FROM lawrentian.currentissue_article WHERE section = :sec";
    const string GET_ARTICLE_IDS = "SELECT idarticle FROM lawrentian.currentissue_article";
}
using namespace AWDBCCommands;
using namespace std;

ArticleWorkspaceDBC::ArticleWorkspaceDBC(Client* c):DatabaseController(c)
{

}

ArticleWorkspaceDBC::~ArticleWorkspaceDBC()
{

}


vector<int>* ArticleWorkspaceDBC::getAllArticleIDs(){
    vector<int>* numz = new vector<int>();
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(AWDBCCommands::GET_ARTICLE_IDS));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){

        while(result->next()){
            numz->push_back(result->value(0).toInt());
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return numz;
}



/**
 * Copied from an equivalent method in CirculationWindowDBC.
 * Remember: this only works because the vector is in ascending order.
 * @brief ArticleWorkspaceDBC::getNextAvailableArticleID
 * @return
 */
int ArticleWorkspaceDBC::getNextAvailableArticleID(){

    int nextInt;

    vector<int>* nums = this->getAllArticleIDs();

    //if empty ret 1
    if(nums->end() == nums->begin()){
        return 1;
    }

    //else iterate
    vector<int>::iterator it = nums->begin();
    while(it != (nums->end()-1) && *(it+1) == *(it)+1){
        ++it;
    }
    nextInt = (*it)+1;


    return nextInt;
}


vector<Article *> *ArticleWorkspaceDBC::getSectionArticles(int section){
    vector<Article*>* youreATallGlassOfWaterArentYouSpencer = new vector<Article*>;
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(AWDBCCommands::GET_ARTICLE_BY_SECTION));
    query->bindValue(":sec",section);


    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            int id = result->value(0).toInt();
            string title = result->value(1).toString().toStdString();
            string description = result->value(2).toString().toStdString();
            int section = result->value(3).toInt();
            int writerLUID = result->value(4).toInt();
            int photographerLUID = result->value(5).toInt();
            string issueDate = result->value(6).toString().toStdString();
            Article* nextArticle = new Article(issueDate, title, description, section, writerLUID, photographerLUID);
            nextArticle->setId(id);

            youreATallGlassOfWaterArentYouSpencer->push_back(nextArticle);
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return youreATallGlassOfWaterArentYouSpencer;
}

vector<int> ArticleWorkspaceDBC::collectWriterForTimesheet(QDate currentDate)
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

void ArticleWorkspaceDBC::generateWriterTimesheet(int writerId, int articlesOnTime, int articlesLate, QDate issueDate)
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

string ArticleWorkspaceDBC::collectArticleSection(int articleId){
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

string ArticleWorkspaceDBC::collectArticleTitle(int articleId)
{
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

vector<int> ArticleWorkspaceDBC::collectArticleIdForTimesheet(QDate currentDate, int writerId)
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
