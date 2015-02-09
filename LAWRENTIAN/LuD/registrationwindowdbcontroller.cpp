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
    cout << "Hi, I am RWDBC." << endl;
}

void RegistrationWindowDBController::init(Client *c){
    Client* cp = c;
    client = cp;
    cout << "RWDBC recieved the client at "<<cp<<endl;
    cout << "The client will now do a trick."<<endl;
    client->execute("shiiiit");
}


void RegistrationWindowDBController::addEmployee(Employee* e) {
    cout << "Inserting new employee named " << e->getName() << endl;

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

    cout << "RWDBC: Client is at " << client << endl;
    cout << "RWDBC: this is " << this << endl;

    /*
    Client* debugClient = new Client();
    debugClient->connect();
    client->execute(query);
    */

    client->execute(query);
}


RegistrationWindowDBController::~RegistrationWindowDBController()
{

}

