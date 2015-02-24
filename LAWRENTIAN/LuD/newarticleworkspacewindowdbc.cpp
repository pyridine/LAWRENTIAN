#include "newarticleworkspacewindowdbc.h"
#include "permissiondef.h"
#include "titledef.h"
#include <iostream>

using namespace std;
namespace NAWWDBCCommands {
    const string GET_WRITERS_FROM_SECTION = "SELECT lawrentian.employee.name,lawrentian.employee.luid FROM lawrentian.employee JOIN lawrentian.employee_permission ON lawrentian.employee.luid = lawrentian.employee_permission.luid WHERE title = :wri AND token = :sec";

    const string DEL_ART = "DELETE FROM lawrentian.currentissue_article WHERE idarticle = :id";

    const string GET_PHOTOGRAPHERS = "SELECT lawrentian.employee.name,lawrentian.employee.luid FROM lawrentian.employee WHERE title = :photi";
}
using namespace NAWWDBCCommands;
NewArticleWorkspaceWindowDBC::NewArticleWorkspaceWindowDBC(Client *c):DatabaseController(c)
{

}

NewArticleWorkspaceWindowDBC::~NewArticleWorkspaceWindowDBC()
{

}

void NewArticleWorkspaceWindowDBC::addArticle(Article* newArticle){
    deleteArticle(newArticle);
}
void NewArticleWorkspaceWindowDBC::deleteArticle(Article* newArticle){
    deleteArticle(newArticle);
}

vector<pair<string,int>*>* NewArticleWorkspaceWindowDBC::getListOfWritersForSection(int sec){

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::GET_WRITERS_FROM_SECTION));
    query->bindValue(":wri",TitleDef::WRITER);
    query->bindValue(":sec",sec);


    //cout << query->lastQuery().toStdString() << endl;

    vector<pair<string,int>*>* writers = new vector<pair<string,int>*>;

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            pair<string,int>* nextWriter = new pair<string,int>;
            nextWriter->first = result->value(0).toString().toStdString();
            nextWriter->second = result->value(1).toInt();
            writers->push_back(nextWriter);
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }
    return writers;
}

vector<pair<string,int>*>* NewArticleWorkspaceWindowDBC::getListOfPhotographers(){

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::GET_PHOTOGRAPHERS));
    query->bindValue(":photi",TitleDef::PHOTOGRAPHER);

    vector<pair<string,int>*>* phographers = new vector<pair<string,int>*>;

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            pair<string,int>* nextPho = new pair<string,int>;
            nextPho->first = result->value(0).toString().toStdString();
            nextPho->second = result->value(1).toInt();
            phographers->push_back(nextPho);
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }
    return phographers;
}
