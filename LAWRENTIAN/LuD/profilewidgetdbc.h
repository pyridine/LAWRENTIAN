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
};

#endif // PROFILEWIDGETDBC_H
