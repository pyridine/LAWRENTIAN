#ifndef LOGINWINDOWDBCONTROLLER_H
#define LOGINWINDOWDBCONTROLLER_H
#include <string>
#include "client.h"
#include "permissions.h"

using namespace std;

class LoginWindowDBController
{
public:
    LoginWindowDBController();
    ~LoginWindowDBController();
    Client* getClient() const;
    void init(Client* c);
    int getLUID(string usname, string passw);
    vector<PToken>* getEmployeePermissions(int LUID);
    string getEmployeeName(int LUID);
    bool isApproved(int luid);
    vector<PToken>* getEmployeeTitlePermissions(int LUID);
    int getEmployeetitle(int LUID);

    void __DEBUG__POPULATE_TITLE_PERMISSIONS(); /*For use during development*/

private:
    void __insertTitlePermission(int titleID,int tokenID); /*For use during development*/
    Client* client;
};




#endif // LOGINWINDOWDBCONTROLLER_H
