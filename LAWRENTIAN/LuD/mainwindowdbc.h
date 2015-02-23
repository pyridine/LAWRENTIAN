#ifndef MAINWINDOWDBC_H
#define MAINWINDOWDBC_H
#include "client.h"
#include "permissiondef.h"

class MainWindowDBC : public DatabaseController
{
public:
    MainWindowDBC(Client* c);
    ~MainWindowDBC();

    //I only use methods from DatabaseController.

};

#endif // MAINWINDOWDBC_H
