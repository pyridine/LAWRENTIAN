#include "registrationwindowdbcontroller.h"
#include <string>
#include <iostream>

using namespace std;

namespace RWDBCcommands {
    const string SQL_ADD_EMPLOYEE = "INSERT INTO lawrentian.employee (luid, name, title, phone, email, username, password, approved) VALUES (:luid, :name, :title, :phone, :email, :username, :password, :approved);";
}

using namespace RWDBCcommands;

RegistrationWindowDBController::RegistrationWindowDBController()
{
    cout << "[Created] RWDBC." << endl;
}

void RegistrationWindowDBController::init(Client *c){
    client = c;
}


void RegistrationWindowDBController::addEmployee(Employee* e) {
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(RWDBCcommands::SQL_ADD_EMPLOYEE));

    query->bindValue(":luid",e->getLuId());
    query->bindValue(":name",QString::fromStdString(e->getName()));
    query->bindValue(":title",QString::fromStdString(e->getTitle()));
    query->bindValue(":phone",QString::fromStdString(e->getPhoneNumber()));
    query->bindValue(":email",QString::fromStdString(e->getEmail()));
    query->bindValue(":username",QString::fromStdString(e->getUsername()));
    query->bindValue(":password",QString::fromStdString(e->getPassword()));
    query->bindValue(":approved",e->getApproved());

    client->execute(query);
}


RegistrationWindowDBController::~RegistrationWindowDBController()
{

}

