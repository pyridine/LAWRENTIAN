#ifndef EDITEMPLOYEEINFODBC_H
#define EDITEMPLOYEEINFODBC_H

#include <string>
#include <vector>
#include "client.h"
#include "databasecontroller.h"

using namespace std;

class EditEmployeeInfoDBC : public DatabaseController
{
public:
    EditEmployeeInfoDBC(Client* c);
    ~EditEmployeeInfoDBC();

    void saveEmployeeChanges(string oldName, string newName, int luid, string title, string email, string phone, int approved);
    vector<string> collectRegisteredNames();
    int collectLuid(string username);
    string collectTitle(string username);
    string collectEmail(string username);
    string collectPhone(string username);
    int collectApproved(string username);
};

#endif // EDITEMPLOYEEINFODBC_H
