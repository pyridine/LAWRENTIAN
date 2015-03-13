#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdlib.h>
#include <string>

using namespace std;

class Employee
{
public:
    Employee(string name, int luId, string email, string title, string phoneNumber, string username, string password, int approved);
    ~Employee();

    string getName();
    int getLuId();
    string getEmail();
    string getPhoneNumber();
    string getTitle();
    string getUsername();
    string getPassword();
    int getApproved();

private:
    string name;
    int luId;
    string title;
    string email;
    string phoneNumber;
    string username;
    string password;
    int approved;
};

#endif // EMPLOYEE_H
