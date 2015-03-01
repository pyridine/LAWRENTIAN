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

    int getAvailableRouteId();
private:
    vector<int> *getAllRouteNums();
    Route* getRoute(int routeId);
    int findMissingNumber(vector<int>* nums);

};

#endif // CIRCULATIONWINDOWDBC_H
