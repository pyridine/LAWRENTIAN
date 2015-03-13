#include "registrationwindowdbcontroller.h"
#include <string>
#include <iostream>

using namespace std;
using namespace RWDBCcommands;

RegistrationWindowDBController::RegistrationWindowDBController()
{
    cout << "Hi, I am RWDBC." << endl;
}

void RegistrationWindowDBController::init(Client *cp){
    RegistrationWindowDBController::client = cp;
}


void RegistrationWindowDBController::addEmployee(Employee* e){
    cout << "begegege" << endl;
    QSqlQuery query;
    query.prepare(QString::fromStdString(RWDBCcommands::SQL_ADD_EMPLOYEE));
    query.bindValue(":luid",e->getLuId());
    query.bindValue(":name",QString::fromStdString(e->getName()));
    query.bindValue(":title",QString::fromStdString(e->getTitle()));
    query.bindValue(":phone",QString::fromStdString(e->getPhoneNumber()));
    query.bindValue(":email",QString::fromStdString(e->getEmail()));
    query.bindValue(":username",QString::fromStdString(e->getUsername()));
    query.bindValue(":password",QString::fromStdString(e->getPassword()));
    query.bindValue(":approved",e->getApproved());
    client->execute(&query);
}


RegistrationWindowDBController::~RegistrationWindowDBController()
{

}

