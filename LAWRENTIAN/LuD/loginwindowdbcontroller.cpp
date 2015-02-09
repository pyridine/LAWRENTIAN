#include "loginwindowdbcontroller.h"
#include <iostream>

using namespace std;

namespace LWDBCcommands {
    const string SELECT_LUID_FROM_LOGIN_CREDENTIALS = "SELECT luid FROM lawrentian.employee WHERE username = ? AND password = ?";
    const string GET_TITLE = "SELECT title FROM lawrentian.employee WHERE luid = :luid;";
    const string GET_APPROVED = "SELECT approved FROM lawrentian.employee WHERE luid = :luid;";
    const string GET_PERMISSIONS = ".......";
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
        cout << "error: " << result->lastError().text().toStdString() << endl;
    }

}


LoginWindowDBController::~LoginWindowDBController()
{

}

