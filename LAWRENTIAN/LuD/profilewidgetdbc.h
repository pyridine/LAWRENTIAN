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
};

#endif // PROFILEWIDGETDBC_H
