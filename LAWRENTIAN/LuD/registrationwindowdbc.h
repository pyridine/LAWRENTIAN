#ifndef REGISTRATIONWINDOWDBCONTROLLER_H
#define REGISTRATIONWINDOWDBCONTROLLER_H


#include <string>
#include "employee.h"
#include "client.h"
#include "databasecontroller.h"

using namespace std;


class RegistrationWindowDBC : public DatabaseController
{

public:
    /*Construction*/
    RegistrationWindowDBC(Client* c);
    ~RegistrationWindowDBC();

    /*Database Commands*/
    void addEmployee(Employee* e);


};


#endif // REGISTRATIONWINDOWDBCONTROLLER_H
