#ifndef LOGINWINDOWDBCONTROLLER_H
#define LOGINWINDOWDBCONTROLLER_H
#include <string>
#include <QtSql>
#include "client.h"

using namespace std;

namespace LWDBCcommands {
    const string SELECT_USERNAME_PASSWORD_COMBINATION = "SELECT luid FROM lawrentian.employee WHERE username = ':username' AND password = ':password';";
    const string GET_TITLE = "SELECT title FROM lawrentian.employee WHERE luid = ':luid'";
}

class LoginWindowDBController
{
public:
    LoginWindowDBController();
    ~LoginWindowDBController();
    Client* getClient();
    void init(Client* c);
    bool attemptLogin(string usname, string passw);

private:
    Client* client;
};




#endif // LOGINWINDOWDBCONTROLLER_H
