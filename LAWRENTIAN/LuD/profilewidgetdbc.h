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
    string collectArticleSection(int articleId);
    string collectArticleTitle(int articleId);
    vector<int> collectArticleIdForTimesheet(QDate currentDate, int writerId);
    string collectProbationApproval(QDate currentDate, int luid);
    vector<string> collectRegistrationApprovals();
    vector<int> collectWriterForTimesheet(QDate currentDate);
    void generateWriterTimesheet(int writerId, int articlesOnTime, int articlesLate, QDate issueDate);
    void deleteWriterTimesheetRecords(QDate issueDate);
    int collectArticlesOnTime(int writerId, QDate issueDate);
    int collectArticlesLate(int writerId, QDate issueDate);
    int writerTimesheetExists(QDate issueDate);
    void setCurrentIssueDate(QDate issueDate);
    QDate collectLatestIssueDate();
    void setHoursWorked(int luid, QDate issueDate, int hoursWorked);
    int getHoursWorked(int luid, QDate issueDate);
    vector<int> collectPotentialProbationApprovals(QDate currentDate);
};

#endif // PROFILEWIDGETDBC_H
