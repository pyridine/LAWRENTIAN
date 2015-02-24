#include "articleworkspacedbc.h"
#include <iostream>

namespace AWDBCCommands {
    const string GET_ARTICLE_BY_SECTION = "SELECT * FROM lawrentian.currentissue_article WHERE section = :sec";
}
using namespace AWDBCCommands;
using namespace std;

ArticleWorkspaceDBC::ArticleWorkspaceDBC(Client* c):DatabaseController(c)
{

}

ArticleWorkspaceDBC::~ArticleWorkspaceDBC()
{

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

            youreATallGlassOfWaterArentYouSpencer->push_back(nextArticle);
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return youreATallGlassOfWaterArentYouSpencer;
}
