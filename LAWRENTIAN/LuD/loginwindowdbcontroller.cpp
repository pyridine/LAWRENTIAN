#include "loginwindowdbcontroller.h"
#include <iostream>


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

LoginWindowDBController::LoginWindowDBController()
{
    cout << "Hi, I am LWDBC." << endl;
}


Client *LoginWindowDBController::getClient() const{
    cout << "LWDBC is giving the client from " << client << endl;
    cout << "proof that it works from this address:" << endl;
    client->execute("sdfs");
    return client;
}

void LoginWindowDBController::init(Client *c){
    client = c;
    cout << "LWDBC recieved client at memaddress " << c << endl;
}

int LoginWindowDBController::getLUID(string usname, string passw){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(LWDBCcommands::SELECT_LUID_FROM_LOGIN_CREDENTIALS));

    query->addBindValue(QString::fromStdString(usname));
    query->addBindValue(QString::fromStdString(passw));

    QSqlQuery* result = client->execute(query);
        cout << query->executedQuery().toStdString()<<endl;
        if(result->next()){
            return result->value(0).toInt();
        }
        else{
            return -1;
        }
}

bool LoginWindowDBController::isApproved(int luid){
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
        cout << "error: " << result->lastError().text().toStdString() << endl;
    }
    return false;
}

string LoginWindowDBController::getEmployeeName(int luid){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(LWDBCcommands::GET_NAME));

    query->bindValue(":luid",luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        result->next();
        return result->value(0).toString().toStdString();
    }else{
        cout << "error: " << result->lastError().text().toStdString() << endl;
    }

}

vector<PToken>* LoginWindowDBController::getEmployeePermissions(int LUID){
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

int LoginWindowDBController::getEmployeetitle(int LUID){
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


vector<PToken>* LoginWindowDBController::getEmployeeTitlePermissions(int LUID){
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

void LoginWindowDBController::__DEBUG__POPULATE_TITLE_PERMISSIONS(){

    //from admin to photographer
    for(int nextTitleID = 0; nextTitleID <= 19; nextTitleID++ ){
        vector<PToken> allTitleTokens = Permissions::__DEBUG_GET_PERMISSION_LIST_FOR_TITLE(static_cast<Title>(nextTitleID));

        vector<PToken>::iterator titleTokens = allTitleTokens.begin();
        while(titleTokens != allTitleTokens.end()){
            cout << "inserting title " << nextTitleID << " token " << *titleTokens << endl;
            LoginWindowDBController::__insertTitlePermission(nextTitleID,*titleTokens);
            ++titleTokens;
        }

    }
}

void LoginWindowDBController::__insertTitlePermission(int titleID, int tokenID){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(LWDBCcommands::INSERT_TITLE_PERMISSION));

    query->bindValue(":ti",titleID);
    query->bindValue(":to",tokenID);

    client->execute(query);
}

LoginWindowDBController::~LoginWindowDBController()
{

}

