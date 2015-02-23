#ifndef PERMISSIONS_H
#define PERMISSIONS_H
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Permissions
{
public:
    Permissions(vector<int>* p);
    Permissions();
    ~Permissions();



    bool hasPermission(int p);

    static vector<int>* __DEBUG_GET_PERMISSION_LIST_FOR_TITLE(int t);

private:
    vector<int>* perms;

};

#endif // PERMISSIONS_H
