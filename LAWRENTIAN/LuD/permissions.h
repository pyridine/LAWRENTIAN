#ifndef PERMISSIONS_H
#define PERMISSIONS_H
#include "PermissionDefinitions.h"
#include <string>
#include <vector>
using namespace PermissionDefinitions;
using namespace std;

class Permissions
{
public:
    Permissions(vector<PToken> &p, int id);
    ~Permissions();

    bool hasPermission(PToken p);

    static string translatePermission(PToken p);

private:
    int LUID;
    vector<PToken> perms;

};

#endif // PERMISSIONS_H
