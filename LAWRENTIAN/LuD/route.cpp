#include "route.h"
#include <vector>
#include "route.h"
#include <string>

using namespace std;



Route::Route(vector<RoutePoint> *r)
{
    Route::route = r;
}

Route::Route()
{

}


void Route::addNode(RoutePoint* node, vector<RoutePoint>::iterator where)
{
    vector<RoutePoint>::iterator it = where;
    route->insert(it,*node);
}
vector<Route::RoutePoint>::iterator Route::begin()
{
    return route->begin();
}
void Route::deleteNode(vector<Route::RoutePoint>::iterator where)
{
    route->erase(where);

}

vector<Route::RoutePoint>::iterator Route::end()
{
    return route->end();
}

Route::~Route()
{
    delete(&route);
}
