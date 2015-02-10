#ifndef EMPLOYEETABDBCONTROLLER_H
#define EMPLOYEETABDBCONTROLLER_H

#include "client.h"
#include <QTableWidgetItem>
#include <utility>
#include "mainwindow.h"

using namespace std;

class EmployeeTabDBController
{
public:
    EmployeeTabDBController();
    ~EmployeeTabDBController();
    void init(Client* c);

    //DB commands
    vector<vector<string>>* getRegularEmployeeView();
    vector<vector<string>>* getPrivilegedEmployeeView();
    vector<vector<string>>* getFullEmployeeView();
    int getNumberOfEmployees();
    void unnaproveEmployee(int luid);
    void approveEmployee(int luid);
    //         :)

private:
    Client* client;

};

#endif // EMPLOYEETABDBCONTROLLER_H
