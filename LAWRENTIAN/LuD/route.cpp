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

vector<Route::RoutePoint>::iterator Route::at(int n){
    vector<RoutePoint>::iterator it = route->begin();
    if(n > 0){
        while(n != 0){
            it++;
            n--;
        }
    }
    return it;
}

//void Route::insert(RoutePoint* r, vector<RoutePoint>::iterator it){
//    route->insert(it,r); //Doesn't work for some reason
//}


void Route::swapPoints(vector<RoutePoint>::iterator first, vector<RoutePoint>::iterator second){
    std::iter_swap(first,second);
}

void Route::insert(RoutePoint* node, vector<RoutePoint>::iterator where)
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
