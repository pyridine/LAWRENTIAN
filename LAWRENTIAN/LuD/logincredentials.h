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
    void setPermissions(vector<PToken>* v);
    void setID(int id);
    void setTitle(int t);

    int getTitle();
    QString getName();
    vector<PToken>* getPermissions();
    int getLUID();

private:
    QString realName;
    vector<PToken>* permissions;
    int luid;
    int title;


};

#endif // LOGINCREDENTIALS_H
