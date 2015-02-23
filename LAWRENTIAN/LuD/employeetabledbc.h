#ifndef EMPLOYEETABDBCONTROLLER_H
#define EMPLOYEETABDBCONTROLLER_H

#include "client.h"
#include <QTableWidgetItem>
#include <utility>
#include "mainwindow.h"
#include "databasecontroller.h"

using namespace std;

class EmployeeTableDBC : public DatabaseController
{
public:
    /*Construction*/
    EmployeeTableDBC(Client* c);
    ~EmployeeTableDBC();

    /*Database Commands*/
    vector<vector<string>>* getRegularEmployeeView();
    vector<vector<string>>* getPrivilegedEmployeeView();
    vector<vector<string>>* getFullEmployeeView();
    int getNumberOfEmployees();
    int getNumUnregistered();
    void unnaproveEmployee(int luid);
    void approveEmployee(int luid);
};

#endif // EMPLOYEETABDBCONTROLLER_H
