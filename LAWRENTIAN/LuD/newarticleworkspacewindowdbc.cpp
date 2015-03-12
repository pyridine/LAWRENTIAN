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
        ":photographer, :issueDate) "
        "ON DUPLICATE KEY UPDATE title=:title, description=:description, section=:section, writer=:writer, "
        "photographer=:photographer, issueDate=:issueDate";

const string GET_ALL_PHOTOGRAPHERS = /*This command is unused.*/
        "SELECT lawrentian.employee.name,lawrentian.employee.luid "
        "FROM lawrentian.employee "
        "WHERE title = :photi";

const string GET_PHOTOGRAPHERS_EXCLUSION =
        "SELECT lawrentian.employee.name,lawrentian.employee.luid "
        "FROM lawrentian.employee "
        "WHERE title = :photi AND lawrentian.employee.luid != :exclusion";

const string SELECT_ARTICLE_BY_TITLE =
        "SELECT * "
        "FROM lawrentian.currentissue_article "
        "WHERE title = :ti";

const string SELECT_ARTICLE_BY_TITLE_AND_NOT_ID =
        "SELECT * "
        "FROM lawrentian.currentissue_article "
        "WHERE title = :ti AND idarticle != :id";



const string DELETE_ALL_PHOTOS_BY_ID =
        "DELETE FROM lawrentian.photo "
        "WHERE idarticle = :art";

const string ADD_A_PHOTO =
        "INSERT INTO lawrentian.photo "
            "(filename,idsection,idarticle,idPhotographer) "
        "VALUES "
            "(:file, :section, :article, :photog)";


}
using namespace NAWWDBCCommands;
NewArticleWorkspaceWindowDBC::NewArticleWorkspaceWindowDBC(Client *c):DatabaseController(c)
{

}

NewArticleWorkspaceWindowDBC::~NewArticleWorkspaceWindowDBC()
{

}

QDate NewArticleWorkspaceWindowDBC::collectLatestIssueDate()
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

void NewArticleWorkspaceWindowDBC::addArticle(Article* art)
{
    deleteArticle(art->getId());

    QSqlQuery *query = new QSqlQuery;
    query->prepare(QString::fromStdString(NAWWDBCCommands::SUBMIT_ARTICLE));
    query->bindValue(":idarticle",art->getId());
    query->bindValue(":title", art->QGetTitle());
    query->bindValue(":description", art->QGetDescription());
    query->bindValue(":section", art->getSection());
    query->bindValue(":writer", art->getWriter());
    query->bindValue(":photographer", art->getPhotographer());
    query->bindValue(":issueDate", art->QGetIssueDate());
    QSqlQuery* result = client->execute(query);
    QSqlError err = query->lastError();
    if(err.isValid()){
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }
    return;
}
void NewArticleWorkspaceWindowDBC::deleteArticle(int articleID){
    //deleteArticle(newArticle); //RECURSION! FOREVER! yo man. chill. There's cntrl + C.

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::DELETE_ARTICLE)); //It's impossible (probably) to assign a non-writer to an article, so this should be fine.
    query->bindValue(":id",articleID);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(err.isValid())
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    else
        cout << "successfully deleted!" << endl;
    return;
}

bool NewArticleWorkspaceWindowDBC::isArticleTitleExistent(string title){

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::SELECT_ARTICLE_BY_TITLE));
    query->bindValue(":ti",QString::fromStdString(title));
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    bool existent = false;

    if(!err.isValid()){
        existent = result->next();
    }
    else{
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }
    return existent;
}

bool NewArticleWorkspaceWindowDBC::isArticleTitleAlreadyInUse(string title,int id){

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::SELECT_ARTICLE_BY_TITLE_AND_NOT_ID));
    query->bindValue(":ti",QString::fromStdString(title));
    query->bindValue(":id",id);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    bool inUse = false;

    if(!err.isValid()){
        inUse =  result->next();
    }
    else{
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }
    return inUse;
}

string NewArticleWorkspaceWindowDBC::translateWriterName(int luid){
    /*First: get the assigned writer.*/
    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT name FROM lawrentian.employee WHERE luid = :lui");
    query->bindValue(":lui",luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        result->next();
        return result->value(0).toString().toStdString();
    }
    else{
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
        return "error";
    }
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
            writers->push_back(nextWriter);
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
            writers->push_back(nextWriter);
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
            phographers->push_back(nextPho);
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
            phographers->push_back(nextPho);
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }
    return phographers;
}


void NewArticleWorkspaceWindowDBC::deleteMyPhotos(int articleId){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(NAWWDBCCommands::DELETE_ALL_PHOTOS_BY_ID));
    query->bindValue(":art",articleId);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(err.isValid()){
        cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
    }
    return;
}

void NewArticleWorkspaceWindowDBC::addMyPhotos(QStringList& imgPaths,int articleID,
                                               int sectionID,int photographerID){
    QSqlQuery* query = new QSqlQuery();

    for(int i = 0; i < imgPaths.size(); ++i){ //I miss my while loops :(
        cout << "adding photo record to db: " << imgPaths.at(i).toStdString();
        query->prepare(QString::fromStdString(NAWWDBCCommands::ADD_A_PHOTO));
        query->bindValue(":file",imgPaths.at(i));
        query->bindValue(":section",sectionID);
        query->bindValue(":article",articleID);
        query->bindValue(":photog",photographerID);
        QSqlQuery* result = client->execute(query);
        QSqlError err = result->lastError();

        if(err.isValid()){
            cout << "!SQL ERROR: " << result->lastError().databaseText().toStdString() << endl;
        }
    }
    return;

}
