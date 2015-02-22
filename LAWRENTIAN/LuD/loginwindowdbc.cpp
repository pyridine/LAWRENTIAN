#include "loginwindowdbc.h"
#include <iostream>
#include <qsql.h>
#include "databasecontroller.h"
#include "client.h"

using namespace std;

namespace LWDBCcommands {
    const string SELECT_LUID_FROM_LOGIN_CREDENTIALS = "SELECT luid FROM lawrentian.employee WHERE username = ? AND password = ?";
    const string GET_NAME = "SELECT name FROM lawrentian.employee WHERE luid = :luid";
    const string GET_APPROVED = "SELECT approved FROM lawrentian.employee WHERE luid = :luid";
    const string GET_TITLE = "SELECT title FROM lawrentian.employee WHERE luid = :luid";
    const string GET_EMPLOYEE_EXCEPTION_PERMISSIONS = "SELECT token FROM lawrentian.employee_permission WHERE luid = :luid";
    const string GET_TITLE_PERMISSIONS = "SELECT token FROM lawrentian.title_permission WHERE title = :title";
    const string INSERT_TITLE_PERMISSION = "INSERT INTO lawrentian.title_permission (title,token) VALUES (:ti,:to)";
}
using namespace LWDBCcommands;
using namespace std;


LoginWindowDBC::LoginWindowDBC(Client* c):DatabaseController(c)
{
    cout << "[Created] LWDBC" << endl;
}

int LoginWindowDBC::getLUID(string usname, string passw){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(LWDBCcommands::SELECT_LUID_FROM_LOGIN_CREDENTIALS));

    query->addBindValue(QString::fromStdString(usname));
    query->addBindValue(QString::fromStdString(passw));

    QSqlQuery* result = client->execute(query);
        if(result->next()){
            return result->value(0).toInt();
        }
        else{
            return -1;
        }
}

bool LoginWindowDBC::isApproved(int luid){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(LWDBCcommands::GET_APPROVED));

    query->bindValue(":luid",luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            return result->value(0).toInt();
        }
    }else{
        return false;
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return false;
}

string LoginWindowDBC::getEmployeeName(int luid){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(LWDBCcommands::GET_NAME));

    query->bindValue(":luid",luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        result->next();
        return result->value(0).toString().toStdString();
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }

}

vector<PToken>* LoginWindowDBC::getEmployeePermissions(int LUID){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(LWDBCcommands::GET_EMPLOYEE_EXCEPTION_PERMISSIONS));
    query->bindValue(":luid",LUID);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<PToken>* permz = new vector<PToken>();

    if(!err.isValid()){
        while(result->next()){
            int nextPTokenID = result->value(0).toString().toInt();
            PToken nextToken = static_cast<PToken>(nextPTokenID);
            permz->push_back(nextToken);
        }
        return permz;


    }else{
        cout << "error: " << result->lastError().text().toStdString() << endl;
    }


}

int LoginWindowDBC::getEmployeetitle(int LUID){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(LWDBCcommands::GET_TITLE));

    query->bindValue(":luid",LUID);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        result->next();
        return result->value(0).toInt();
    }else{
        cout << "error: " << result->lastError().text().toStdString() << endl;
    }

}


vector<PToken>* LoginWindowDBC::getEmployeeTitlePermissions(int LUID){
    int title = getEmployeetitle(LUID);

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(LWDBCcommands::GET_TITLE_PERMISSIONS));

    query->bindValue(":title",title);


    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<PToken>* permz = new vector<PToken>();

    if(!err.isValid()){
        while(result->next()){
            int nextPTokenID = result->value(0).toString().toInt();
            PToken nextToken = static_cast<PToken>(nextPTokenID);
            permz->push_back(nextToken);
        }
        return permz;


    }else{
        cout << "error: " << result->lastError().text().toStdString() << endl;
    }


}

void LoginWindowDBC::__DEBUG__POPULATE_TITLE_PERMISSIONS(){

    //from admin to photographer
    for(int nextTitleID = 0; nextTitleID <= 19; nextTitleID++ ){
        vector<PToken>* allTitleTokens = Permissions::__DEBUG_GET_PERMISSION_LIST_FOR_TITLE(static_cast<Title>(nextTitleID));

        vector<PToken>::iterator titleTokens = allTitleTokens->begin();
        while(titleTokens != allTitleTokens->end()){
            cout << "inserting title " << nextTitleID << " token " << *titleTokens << endl;
            LoginWindowDBC::__DEBUG__insertTitlePermission(nextTitleID,*titleTokens);
            ++titleTokens;
        }

    }
}

void LoginWindowDBC::__DEBUG__insertTitlePermission(int titleID, int tokenID){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(LWDBCcommands::INSERT_TITLE_PERMISSION));

    query->bindValue(":ti",titleID);
    query->bindValue(":to",tokenID);

    client->execute(query);
}

LoginWindowDBC::~LoginWindowDBC()
{

}

