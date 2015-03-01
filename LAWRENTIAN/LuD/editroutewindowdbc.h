#ifndef EDITROUTEWINDOWDBC_H
#define EDITROUTEWINDOWDBC_H
#include <utility>
#include "databasecontroller.h"

using std::vector;
using std::string;

#include "route.h"
#include "client.h"

class EditRouteWindowDBC : public DatabaseController
{
public:
    EditRouteWindowDBC(Client* c);
    ~EditRouteWindowDBC();
    vector<int>* getAllLocationIDs();
    void insertRoute(Route* r, int routeID); //Deletes before insering for simplicity. So you use this for add and edit.
    void dropRoute(int routeID);
    void insertRoutePoint(Route::RoutePoint p, int routeId, int pointOrder);

private:

};

#endif // EDITROUTEWINDOWDBC_H
