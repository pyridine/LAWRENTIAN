#include "permissions.h"
#include "PermissionDefinitions.h" //TODO: Should probably IFNDEF this.

#include <vector>
#include <string>

using namespace PermissionDefinitions;
using namespace std;

permissions::permissions(vector<PToken> &p, int id)
{
    permissions::perms = p;
    permissions::LUID = id;
}

bool permissions::hasPermission(PToken query){
    vector<PToken>::iterator it;

    for(it = perms.begin(); it != perms.end(); ++it){
        if((*it) == query){
            return true;
        }
    }
    return false;
}

permissions::~permissions()
{
    delete(&perms);
}

