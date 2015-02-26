#include "newarticleworkspacewindowdbc.h"
#include "permissiondef.h"
#include "titledef.h"
#include <iostream>

using namespace std;
namespace NAWWDBCCommands {
const string GET_ALL_WRITERS_FROM_SECTION = /*This command is unused.*/
        "SELECT lawrentian.employee.name,lawrentian.employee.luid "
        "FROM lawrentian.employee "
            "JOIN lawrentian.employee_permission ON lawrentian.employee.luid = lawrentian.employee_permission.luid "
        "WHERE title = :wri AND token = :sec "
        "GROUP BY lawrentian.employee.name,lawrentian.employee.luid";

const string GET_WRITERS_FROM_SECTION_EXCLUSION =
        "SELECT lawrentian.employee.name,lawrentian.employee.luid "
        "FROM lawrentian.employee "
            "JOIN lawrentian.employee_permission ON lawrentian.employee.luid = lawrentian.employee_permission.luid "
        "WHERE title = :wri AND token = :sec AND lawrentian.employee.luid != :exclusion "
        "GROUP BY lawrentian.employee.name,lawrentian.employee.luid";

const string GET_ONE_WRITER_FROM_SECTION =
        "SELECT lawrentian.employee.name FROM lawrentian.employee "
        "WHERE luid = :lui "
        "AND EXISTS "
        "( SELECT luid FROM lawrentian.employee_permission WHERE luid = :lui AND token = :sec )";

const string GET_ONE_EMPLOYEE =
        "SELECT lawrentian.employee.name "
        "FROM lawrentian.employee "
        "WHERE luid = :lui";

const string DELETE_ARTICLE =
        "DELETE FROM lawrentian.currentissue_article "
        "WHERE idarticle = :id";

const string SUBMIT_ARTICLE =
        "INSERT INTO lawrentian.currentissue_article (idarticle,title,description,section,writer,"
        "photographer,issueDate) "
        "VALUES (:idarticle, :title, :description, :section, :writer,"
        ":photographer, :issueDate)";

const string GET_ALL_PHOTOGRAPHERS = /*This command is unused.*/
        "SELECT lawrentian.employee.name,lawrentian.employee.luid "
        "FROM lawrentian.employee "
        "WHERE title = :photi";

const string GET_PHOTOGRAPHERS_EXCLUSION =
        "SELECT lawrentian.employee.name,lawrentian.employee.luid "
        "FROM lawrentian.employee "
        "WHERE title = :photi AND lawrentian.employee.luid != :exclusion";


}
using namespace NAWWDBCCommands;
NewArticleWorkspaceWindowDBC::NewArticleWorkspaceWindowDBC(Client *c):DatabaseController(c)
{

}

NewArticleWorkspaceWindowDBC::~NewArticleWorkspaceWindowDBC()
{

}

void NewArticleWorkspaceWindowDBC::addArticle(Article* art)
{
    deleteArticle(art->getId());

    QSqlQuery *query = new QSqlQuery;
    query->prepare(QString::fromStdString(NAWWDBCCommands::SUBMIT_ARTICLE));
    query->bindValue(":idarticle",art->getId()); cout << "articleid" << art->getId() << endl;
    query->bindValue(":title", art->QGetTitle()); cout << "tittl" << art->getTitle() << endl;
    query->bindValue(":description", art->QGetDescription()); cout << "desc" << art->getDescription() << endl;
    query->bindValue(":section", art->getSection()); cout << "sec" << art->getSection() << endl;
    query->bindValue(":writer", art->getWriter()); cout << "writ" << art->getWriter() << endl;
    query->bindValue(":photographer", art->getPhotographer()); cout << "pho" << art->getPhotographer() << endl;
    query->bindValue(":issueDate", art->QGetIssueDate()); cout << "date" << art->getIssueDate() << endl;
    QSqlQuery* result = client->execute(query);
    QSqlError err = query->lastError();
    if(err.isValid()){
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }
    return;
}
void NewArticleWorkspaceWindowDBC::deleteArticle(int articleID){
    //deleteArticle(newArticle); //RECURSION! FOREVER!

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::DELETE_ARTICLE)); //It's impossible (probably) to assign a non-writer to an article, so this should be fine.
    query->bindValue(":id",articleID);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(err.isValid()){
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }
    return;
}

/**
 *
 * Set currentWriter to -1 if there is no currentWriter for the article.
 * Whoever you do pass as the current writer shows up FIRST on the returned list.
 * This is how the article workspace window is loaded pointing to the current writer.
 *
 * @brief NewArticleWorkspaceWindowDBC::getListOfWritersForSection
 * @param sec
 * @param currentWriter
 * @return returns a vector of <writerName,writerLUID>.
 */
vector<pair<string,int>*>* NewArticleWorkspaceWindowDBC::getListOfWritersForSection(int section, int currentWriter){
    vector<pair<string,int>*>* writers = new vector<pair<string,int>*>;

    /*First: get the assigned writer.*/
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::GET_ONE_WRITER_FROM_SECTION)); //It's impossible (probably) to assign a non-writer to an article, so this should be fine.
    query->bindValue(":lui",currentWriter);
    query->bindValue(":sec",section);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            //Push the assigned writer (if any)
            pair<string,int>* nextWriter = new pair<string,int>;
            nextWriter->first = result->value(0).toString().toStdString();
            nextWriter->second = currentWriter;
            writers->push_back(nextWriter); cout << "assigned writer pushed: " << nextWriter->first << "," << nextWriter->second << endl;
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }

    /*Second: get all the other writers from the section.*/
    query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::GET_WRITERS_FROM_SECTION_EXCLUSION));
    query->bindValue(":wri",TitleDef::WRITER);
    query->bindValue(":sec",section);
    query->bindValue(":exclusion",currentWriter);
    result = client->execute(query);
    err = result->lastError();

    if(!err.isValid()){
        //Push the writers
        while(result->next()){
            pair<string,int>* nextWriter = new pair<string,int>;
            nextWriter->first = result->value(0).toString().toStdString();
            nextWriter->second = result->value(1).toInt();
            writers->push_back(nextWriter); cout << "available writer pushed: " << nextWriter->first << "," << nextWriter->second << endl;
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }

    return writers;
}

/**
 * This works the same way as getListOfWriters... So look at the documentation for that one.
 *
 * @brief NewArticleWorkspaceWindowDBC::getListOfPhotographers
 * @param curentPhotographer
 * @return returns a vector of <photographerName,photographerLUID>.
 */
vector<pair<string,int>*>* NewArticleWorkspaceWindowDBC::getListOfPhotographers(int curentPhotographer){
    vector<pair<string,int>*>* phographers = new vector<pair<string,int>*>;

    /*First: get the assigned photographer.*/
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::GET_ONE_EMPLOYEE));
    query->bindValue(":lui",curentPhotographer);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            //Push the assigned photographer, if any.
            pair<string,int>* nextPho = new pair<string,int>;
            nextPho->first = result->value(0).toString().toStdString();
            nextPho->second = curentPhotographer;
            phographers->push_back(nextPho); cout << "assigned pho pushed: " << nextPho->first << "," << nextPho->second << endl;
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }

    /*Second: get all the other photographers.*/
    query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::GET_PHOTOGRAPHERS_EXCLUSION));
    query->bindValue(":photi",TitleDef::PHOTOGRAPHER);
    query->bindValue(":exclusion",curentPhotographer);

    result = client->execute(query);
    err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            //Push everyone else
            pair<string,int>* nextPho = new pair<string,int>;
            nextPho->first = result->value(0).toString().toStdString();
            nextPho->second = result->value(1).toInt();
            phographers->push_back(nextPho); cout << "available pho pushed: " << nextPho->first << "," << nextPho->second << endl;
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }
    return phographers;
}
