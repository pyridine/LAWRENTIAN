#ifndef DATABASECONTROLLER
#define DATABASECONTROLLER
#include "client.h"

using namespace std;

class DatabaseController{
public:
    DatabaseController(Client* c);
    Client* getClient();

    string translateTitle(int titleID);
    string translatePermission(int permID);
    string translateLocation(int locID);
    string translateSection(int secId);


protected:
    Client* client;
};


#endif // DATABASECONTROLLER

