#ifndef PERMISSIONS_H
#define PERMISSIONS_H
#include "PermissionDefinitions.h"
#include <string>
#include <vector>
using namespace PermissionDefinitions;
using namespace std;

class permissions
{
public:
    permissions(vector<PToken> &p, int id);
    ~permissions();

    bool hasPermission(PToken p);


private:
    int LUID;
    vector<PToken> perms;

};

#endif // PERMISSIONS_H
