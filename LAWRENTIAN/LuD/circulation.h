#ifndef CIRCULATION_H
#define CIRCULATION_H

#include <vector>
#include <string>
#include <utility>

using namespace std;

class Circulation
{
    typedef std::pair<string,int> CirculationNode;

public:
    Circulation(vector<CirculationNode> &route);
    ~Circulation();
    void addNode(CirculationNode &node, int pos);
    vector<CirculationNode>::iterator begin();
    vector<CirculationNode>::iterator end();
    void deleteNode(int index);

private:
   vector<CirculationNode> *route;
};

#endif // CIRCULATION_H
