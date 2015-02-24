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
    void addNode(RoutePoint* node, vector<RoutePoint>::iterator where);
    vector<RoutePoint>::iterator begin();
    vector<RoutePoint>::iterator end();
    void deleteNode(vector<RoutePoint>::iterator where);

private:
   vector<RoutePoint> *route;
};

#endif // CIRCULATION_H
