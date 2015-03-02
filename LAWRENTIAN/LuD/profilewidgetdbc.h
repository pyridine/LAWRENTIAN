#ifndef PROFILEWIDGETDBC_H
#define PROFILEWIDGETDBC_H

#include "client.h"
#include "databasecontroller.h"

class ProfileWidgetDBC : public DatabaseController
{
public:
    ProfileWidgetDBC(Client *c);
    ~ProfileWidgetDBC();

    string collectName(int luid);
    string collectTitle(int luid);
    vector<string> collectProbationApprovals(QDate currentDate);
    vector<int> collectWriterForTimesheet(QDate currentDate);
    void generateWriterTimesheet(int writerId, int articlesOnTime, int articlesLate, QDate issueDate);
    void deleteWriterTimesheetRecords(QDate issueDate);
    int collectArticlesOnTime(int writerId, QDate issueDate);
    int collectArticlesLate(int writerId, QDate issueDate);
    int writerTimesheetExists(QDate issueDate);
};

#endif // PROFILEWIDGETDBC_H
