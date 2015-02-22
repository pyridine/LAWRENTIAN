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
    int getEmployeetitle(int LUID);
    bool isApproved(int luid);
    vector<PToken>* getEmployeePermissions(int LUID);
    string getEmployeeName(int LUID);
    vector<PToken>* getEmployeeTitlePermissions(int LUID);

    /*Debug*/
    void __DEBUG__POPULATE_TITLE_PERMISSIONS(); /*For use during development*/
private:
    /*Debug*/
    void __DEBUG__insertTitlePermission(int titleID,int tokenID); /*For use during development*/
};




#endif // LOGINWINDOWDBCONTROLLER_H
