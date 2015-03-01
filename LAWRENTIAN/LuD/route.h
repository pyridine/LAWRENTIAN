#ifndef CIRCULATION_H
#define CIRCULATION_H

#include <vector>
#include <string>
#include <utility>

using namespace std;

class Route
{


public:
    typedef std::pair<int,int> RoutePoint; //location first, numCopies second.
    Route(vector<RoutePoint>* route);
    Route();
    ~Route();
    vector<RoutePoint>::iterator begin();
    vector<RoutePoint>::iterator at(int n);
    vector<RoutePoint>::iterator end();
    //void insert(RoutePoint *r, vector<RoutePoint>::iterator it);
    void insert(RoutePoint* node, vector<RoutePoint>::iterator where);
    void deleteNode(vector<RoutePoint>::iterator where);
    void swapPoints(vector<RoutePoint>::iterator first, vector<RoutePoint>::iterator second);

private:
   vector<RoutePoint> *route;
};

#endif // CIRCULATION_H
