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

    vector<pair<Route *, int> > *getAllRoutes();
    void insertRoute(Route* r, int routeID); //Deletes before insering for simplicity. So you use this for add and edit.
    void dropRoute(int routeID);
    int getAvailableRouteId();
    int sumTotalCopies();
private:
    vector<int> *getAllRouteNums();
    Route* getRoute(int routeId);
    int findMissingNumber(vector<int>* nums);

};

#endif // CIRCULATIONWINDOWDBC_H
