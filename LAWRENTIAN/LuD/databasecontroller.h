#ifndef DATABASECONTROLLER
#define DATABASECONTROLLER
#include "client.h"

using namespace std;

namespace df
{
    const QString dbFormat = "yyyy-MM-dd";
    const QString srvrFormat = "dd MMM, yyyy";
}

class DatabaseController{
public:
    DatabaseController(Client* c);
    Client* getClient();

    string translateTitle(int titleID);
    string translatePermission(int permID);
    string translateLocation(int locID);
    string translateSection(int secID);
    string translateRoute(int rID);


protected:
    Client* client;
};


#endif // DATABASECONTROLLER

