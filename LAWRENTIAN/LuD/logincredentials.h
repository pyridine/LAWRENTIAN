#ifndef LOGINCREDENTIALS_H
#define LOGINCREDENTIALS_H
#include "permissions.h"
#include <utility>
#include <qstring.h>

class LoginCredentials
{
public:
    LoginCredentials();
    ~LoginCredentials();
    void setName(string n);
    void setPermissions(Permissions* v);
    void setID(int id);
    void setTitle(int t);

    int getTitle();
    QString getName();
    Permissions* getPermissions();
    int getLUID();
    bool hasPermission(PToken p);

private:
    QString realName;
    Permissions* permissions;
    int luid;
    int title;


};

#endif // LOGINCREDENTIALS_H
