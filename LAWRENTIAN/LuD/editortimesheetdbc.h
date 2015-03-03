#ifndef EDITORTIMESHEETDBC_H
#define EDITORTIMESHEETDBC_H

#include "client.h"
#include "databasecontroller.h"

class EditorTimesheetDBC : public DatabaseController
{
public:
    EditorTimesheetDBC(Client *c);
    ~EditorTimesheetDBC();

    void setHoursWorked(int luid, QDate issueDate, int hoursWorked);
    int getHoursWorked(int luid, QDate issueDate);
    vector<int> collectEditorForTimesheet(QDate currentDate);
    vector<vector<string>>* getTimesheet(QDate issueDate);
};

#endif // EDITORTIMESHEETDBC_H
