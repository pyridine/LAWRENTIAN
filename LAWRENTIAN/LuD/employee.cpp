#include "employee.h"
#include <string>
#include <iostream>

using namespace std;


Employee::Employee(string name, int luId, string email, string title, string phoneNumber, string username, string password, int approved)
{
    cout << "Hi, I am an employee object." << endl;
Employee::name = name;
Employee::luId = luId;
Employee::email = email;
Employee::phoneNumber = phoneNumber;
Employee::username = username;
Employee::password = password;
Employee::approved = approved;
Employee::title = title;
}

Employee::~Employee()
{

}

string Employee::getName()
{
    return Employee::name;
}

string Employee::getTitle()
{
    return Employee::title;
}

int Employee::getLuId()
{
    return Employee::luId;
}

string Employee::getEmail()
{
    return Employee::email;
}

string Employee::getPhoneNumber()
{
    return Employee::phoneNumber;
}

string Employee::getUsername()
{
    return Employee::username;
}

string Employee::getPassword()
{
    return Employee::password;
}

int Employee::getApproved()
{
    return Employee::approved;
}

