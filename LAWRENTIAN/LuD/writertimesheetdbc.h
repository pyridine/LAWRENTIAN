#ifndef WRITERTIMESHEETDBC_H
#define WRITERTIMESHEETDBC_H

#include "client.h"
#include "databasecontroller.h"

class WriterTimesheetDBC : public DatabaseController
{
public:
    WriterTimesheetDBC(Client *c);
    ~WriterTimesheetDBC();

    vector<int> collectWriterForTimesheet(QDate currentDate);
    void generateWriterTimesheet(int writerId, int articlesOnTime, int articlesLate, QDate issueDate);
    void deleteWriterTimesheetRecords(QDate issueDate);
    int collectArticlesOnTime(int writerId, QDate issueDate);
    int collectArticlesLate(int writerId, QDate issueDate);
    int writerTimesheetExists(QDate issueDate);
};

#endif // WRITERTIMESHEETDBC_H
