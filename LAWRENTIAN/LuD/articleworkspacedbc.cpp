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
            cout << "nextartidnum " << result->value(0).toInt();
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

    cout << "getting next available article ID." << endl;
    vector<int>* nums = this->getAllArticleIDs();


    for(vector<int>::iterator it = nums->begin(); it != nums->end(); it++){
        cout << *it << ",";
    }

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
