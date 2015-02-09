#ifndef LOGINWINDOWDBCONTROLLER_H
#define LOGINWINDOWDBCONTROLLER_H
#include <string>
#include "client.h"

using namespace std;

class LoginWindowDBController
{
public:
    LoginWindowDBController();
    ~LoginWindowDBController();
    Client* getClient() const;
    void init(Client* c);
    int getLUID(string usname, string passw);
    bool isApproved(int luid);

private:
    Client* client;
};




#endif // LOGINWINDOWDBCONTROLLER_H
