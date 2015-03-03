#include "permissionswidgetdbc.h"
#include <vector>
#include <iostream>

#include <QVariant>

namespace PWDBCCommands{
    const string GET_LONG_DESCRIPTION = "SELECT longdescription FROM lawrentian.permissiontokens WHERE idtoken = :tok";
    const string GET_ABBREV_DESCRIPTION = "SELECT description FROM lawrentian.permissiontokens WHERE idtoken = :tok";
    const string GETTOKENIDS = "SELECT idtoken FROM lawrentian.permissiontokens ORDER BY description ASC";
    const string GET_TITLE_TOKENS = "SELECT idTitle from lawrentian.titledefinitions ORDER BY titleName";
    const string GET_TITLE_NAME = "SELECT titleName from lawrentian.titledefinitions WHERE idTitle = :idtit";
    const string GET_EMPLOYEE_NAME = "SELECT name from lawrentian.employee WHERE luid = :lui";
    const string GET_ALL_USER_IDS_AND_NAMES_AND_TITLE = "SELECT luid,name,title from lawrentian.employee ORDER BY name ASC";



    const string DROP_ALL_EMPLOYEE_PERMISSIONS = "DELETE FROM lawrentian.employee_permission WHERE luid = :luid";
    const string ADD_EMPLOYEE_PERMISSION = "INSERT INTO lawrentian.employee_permission (luid,token) VALUES (:lui,:tok)";

    const string DROP_ALL_TITLE_PERMISSIONS = "DELETE FROM lawrentian.title_permission WHERE title = :title";
    const string ADD_TITLE_PERMISSION = "INSERT INTO lawrentian.title_permission (title,token) VALUES (:title,:token)";



    const string GET_EMPLOYEE_EXCEPTION_PERMISSIONS = "SELECT token FROM lawrentian.employee_permission WHERE luid = :luid";
    const string GET_TITLE_PERMISSIONS = "SELECT token FROM lawrentian.title_permission WHERE title = :title";
    const string GET_ALL_PERMISSIONS = "SELECT idtoken FROM lawrentian.permissiontokens";
}
using namespace PWDBCCommands;
using namespace std;

PermissionsWidgetDBC::PermissionsWidgetDBC(Client *c):DatabaseController(c)
{

}

PermissionsWidgetDBC::~PermissionsWidgetDBC()
{

}

string PermissionsWidgetDBC::translatePermission_long(int perm){

    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(PWDBCCommands::GET_LONG_DESCRIPTION));

    query->bindValue(":tok",perm);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            return result->value(0).toString().toStdString();
        } else{
            return "Error";
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return "Error";
    }
}
string PermissionsWidgetDBC::translateEmployee(int empId){

    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(PWDBCCommands::GET_EMPLOYEE_NAME));

    query->bindValue(":lui",empId);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        if(result->next()){
            return result->value(0).toString().toStdString();
        } else{
            return "Error";
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return "Error";
    }
}

void PermissionsWidgetDBC::addPermission_employee(int emp, int perm){
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(PWDBCCommands::ADD_EMPLOYEE_PERMISSION));
    query->bindValue(":lui",emp);
    query->bindValue(":tok",perm);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

void PermissionsWidgetDBC::addPermission_title(int ttl, int perm){
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(PWDBCCommands::ADD_TITLE_PERMISSION));
    query->bindValue(":title",ttl);
    query->bindValue(":token",perm);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}
vector<int>* PermissionsWidgetDBC::getTitlePermissions(int title){
    return this->execute_int_for_intvect(PWDBCCommands::GET_TITLE_PERMISSIONS,":title",title);
}

vector<int> *PermissionsWidgetDBC::getEmployeePermissions(int emp){
    return this->execute_int_for_intvect(PWDBCCommands::GET_EMPLOYEE_EXCEPTION_PERMISSIONS,":luid",emp);
}

vector<std::tuple<int/*id*/,string/*name*/,int/*title*/>*>* PermissionsWidgetDBC::getEmployees(){
    //Unfortunately, I'm just gonna have to write this one, since it's not
    //something I'll be doing even twice.

    vector<std::tuple<int,string,int>*>* employees = new vector<std::tuple<int,string,int>*>();
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(PWDBCCommands::GET_ALL_USER_IDS_AND_NAMES_AND_TITLE));
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            int nextLuid = result->value(0).toInt();
            string nextName = result->value(1).toString().toStdString();
            int nextTitle = result->value(2).toInt();
            employees->push_back(new std::tuple<int,string,int>(nextLuid,nextName,nextTitle));
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return employees;
}

vector<int>* PermissionsWidgetDBC::getTitles(){
    return execute_null_for_intvect(PWDBCCommands::GET_TITLE_TOKENS);
}
vector<int>* PermissionsWidgetDBC::getAllPermissions(){
    return execute_null_for_intvect(PWDBCCommands::GET_ALL_PERMISSIONS);
}


void PermissionsWidgetDBC::dropAllPermission_Title(int title){
    vector<string>* argName = new vector<string>();
    vector<QVariant>* arg = new vector<QVariant>();
    argName->push_back(":title");
    arg->push_back(QVariant(title));
    executeSQLString_Args(PWDBCCommands::DROP_ALL_TITLE_PERMISSIONS,argName,arg);
    return;
}

void PermissionsWidgetDBC::dropAllPermission_Employee(int luid){
    vector<string>* argName = new vector<string>();
    vector<QVariant>* arg = new vector<QVariant>();
    argName->push_back(":luid");
    arg->push_back(QVariant(luid));
    executeSQLString_Args(PWDBCCommands::DROP_ALL_EMPLOYEE_PERMISSIONS,argName,arg);
    return;
}
