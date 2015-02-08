#ifndef LOGINCREDENTIALS_H
#define LOGINCREDENTIALS_H
#include "permissions.h"

class LoginCredentials
{
public:
    LoginCredentials(string &sn, string &ttl, Permissions* p, int id);
    ~LoginCredentials();


private:
    string username;
    string title;
    Permissions* permissions;
    int luid;


};

#endif // LOGINCREDENTIALS_H
