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

