#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdlib.h>
#include <string>

using namespace std;

class Employee
{
public:
    Employee(string name, string luId, string email, string phoneNumber, string username, string password);
    ~Employee();

private:
    string name;
    string luId;
    string email;
    string phoneNumber;
    string username;
    string password;
};

#endif // EMPLOYEE_H
