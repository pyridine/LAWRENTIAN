#include "employee.h"
#include <string>

Employee::Employee(string name, string luId, string email, string phoneNumber, string username, string password)
{
Employee::name = name;
Employee::luId = luId;
Employee::email = email;
Employee::phoneNumber = phoneNumber;
Employee::username = username;
Employee::password = password;
}

Employee::~Employee()
{

}

string Employee::getName()
{
    return Employee::name;
}

string Employee::getLuId()
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

