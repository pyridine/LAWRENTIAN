#ifndef LOGINWINDOWDBCONTROLLER_H
#define LOGINWINDOWDBCONTROLLER_H
#include <string>
#include <QtSql>
#include "client.h"

using namespace std;

class LoginWindowDBController
{
public:
    LoginWindowDBController();
    ~LoginWindowDBController();
    const Client* getClient() const;
    void init(const Client* c);
    int getLUID(string usname, string passw);
    bool isApproved(int luid);

private:
    const Client* client;
};




#endif // LOGINWINDOWDBCONTROLLER_H
