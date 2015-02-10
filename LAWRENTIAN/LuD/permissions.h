#ifndef PERMISSIONS_H
#define PERMISSIONS_H
#include "PermissionDefinitions.h"
#include "titledefinitions.h"
#include <string>
#include <vector>
#include <utility>

using namespace PermissionDefinitions;
using namespace TitleDefinitions;
using namespace std;

class Permissions
{
public:
    Permissions(vector<PToken>* p);
    Permissions();
    ~Permissions();



    bool hasPermission(PToken p);


    static string translatePermission(PToken p);
    static string translateTitle(Title t);

    static vector<PToken>* __DEBUG_GET_PERMISSION_LIST_FOR_TITLE(Title t);

private:
    vector<PToken>* perms;

};

#endif // PERMISSIONS_H
