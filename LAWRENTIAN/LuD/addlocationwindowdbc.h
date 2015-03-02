#ifndef ADDLOCATIONWINDOWDBC_H
#define ADDLOCATIONWINDOWDBC_H

#include "databasecontroller.h"
#include "client.h"

class AddLocationWindowDBC : public DatabaseController
{
public:
    AddLocationWindowDBC(Client* c);
    ~AddLocationWindowDBC();
    void addLocation(int locID, string loc);
    void dropLocation(int LocID);
};

#endif // ADDLOCATIONWINDOWDBC_H
