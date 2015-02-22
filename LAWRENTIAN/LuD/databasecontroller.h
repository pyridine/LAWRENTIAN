#ifndef DATABASECONTROLLER
#define DATABASECONTROLLER
#include "client.h"


/*

  willkommen au DatabaseController. I must be publicly inherited.

*/


class DatabaseController{
public:
    DatabaseController(Client* c);
    Client* getClient();

protected:
    Client* client;
};


#endif // DATABASECONTROLLER

