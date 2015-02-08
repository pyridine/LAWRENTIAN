#ifndef REGISTRATIONWINDOWDBCONTROLLER_H
#define REGISTRATIONWINDOWDBCONTROLLER_H


#include <string>
#include "employee.h"
#include "client.h"

using namespace std;


class RegistrationWindowDBController
{



public:
    RegistrationWindowDBController();
    ~RegistrationWindowDBController();
    void init(const Client* c);
    void addEmployee(Employee* e);

private:
    const Client* client;



};

#endif // REGISTRATIONWINDOWDBCONTROLLER_H
