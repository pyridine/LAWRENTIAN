#ifndef CIRCULATIONWINDOWDBC_H
#define CIRCULATIONWINDOWDBC_H

#include "databasecontroller.h"
#include "route.h"
#include <utility>

using namespace std;

class CirculationWindowDBC : public DatabaseController
{
public:
    CirculationWindowDBC(Client* c);
    CirculationWindowDBC(); //Or else QT gets mad
    ~CirculationWindowDBC();

    vector<pair<Route *, int> *> *getAllRoutes();
    void insertRoute(Route* r, int routeID); //Deletes before insering for simplicity. So you use this for add and edit.
    void dropRoute(int routeID);

private:
    int getAvailableRouteId(); //Really important for inserting
    vector<int> *getAllRouteNums();
    void insertRoutePoint(Route::RoutePoint p, int routeId, int pointOrder);
    Route* getRoute(int routeId);
    int findMissingNumber(vector<int>* v);

};

#endif // CIRCULATIONWINDOWDBC_H
