#ifndef PERMISSIONSWIDGETDBC_H
#define PERMISSIONSWIDGETDBC_H
#include <string>
#include <QString>
#include "databasecontroller.h"
#include <utility>
#include <tuple>


using namespace std;
class PermissionsWidgetDBC : public DatabaseController
{
public:
    PermissionsWidgetDBC(Client* c);
    ~PermissionsWidgetDBC();
    vector<int> getAllEmployeePermissions();



    //string translatePermission_short(int perm); This is already a part of DBC base class.
    string translatePermission_long(int perm);
    void removePermission_employee(int emp,int perm);
    void addPermission_employee(int emp,int perm);
    void removePermission_title(int ttl, int perm);
    void addPermission_title(int ttl, int perm);
    vector<int> *getTitlePermissions(int title);
    vector<int> *getEmployeePermissions(int emp);
    vector<std::tuple<int, string, int> *> *getEmployees();
    vector<int> *getTitles();

};

#endif // PERMISSIONSWIDGETDBC_H
