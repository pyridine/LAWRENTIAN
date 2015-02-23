#ifndef LOGINWINDOWDBCONTROLLER_H
#define LOGINWINDOWDBCONTROLLER_H
#include <string>
#include "client.h"
#include "permissions.h"
#include "databasecontroller.h"

using namespace std;

class LoginWindowDBC : public DatabaseController
{
public:
    /*Contstruction*/
    LoginWindowDBC(Client *c);
    ~LoginWindowDBC();

    /*Database Commands*/
    int getLUID(string usname, string passw);
    int getEmployeeTitle(int LUID);
    bool isApproved(int luid);
    vector<int>* getEmployeePermissions(int LUID);
    string getEmployeeName(int LUID);
    vector<int>* getEmployeeTitlePermissions(int LUID);

    /*For populating permissions*/
    int __getPermissionID(string permission);
    int __getTitleID(string title);


    /*Debug*/
    void __DEBUG__POPULATE_TITLE_PERMISSIONS(); /*For use during development*/
private:
    /*Debug*/
    void __DEBUG__insertTitlePermission(int titleID,int tokenID); /*For use during development*/
};


#endif // LOGINWINDOWDBCONTROLLER_H
