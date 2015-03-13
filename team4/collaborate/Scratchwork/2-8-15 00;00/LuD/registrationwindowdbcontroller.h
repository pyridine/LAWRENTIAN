#ifndef REGISTRATIONWINDOWDBCONTROLLER_H
#define REGISTRATIONWINDOWDBCONTROLLER_H


#include <string>
#include "employee.h"
#include "client.h"

using namespace std;


namespace RWDBCcommands {
    const string SQL_ADD_EMPLOYEE = "INSERT INTO lawrentian.employee (luid, name, title, phone, email, username, password, approved) VALUES (:luid, :name, :title, :phone, :email, :username, :password, :approved);";

}

class RegistrationWindowDBController
{



public:
    RegistrationWindowDBController();
    ~RegistrationWindowDBController();
    void init(Client* c);
    void addEmployee(Employee* e);

private:
    Client* client;



};

#endif // REGISTRATIONWINDOWDBCONTROLLER_H
