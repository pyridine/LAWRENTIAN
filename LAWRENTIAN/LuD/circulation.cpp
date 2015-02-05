#include "circulation.h"
#include <vector>
#include "circulation.h"
#include <string>

using namespace std;



Circulation::Circulation(vector<CirculationNode> &r)
{
    Circulation::route = r;
}

void Circulation::addNode(CirculationNode &node, int insert_pos)
{
    //TODO: Is this the right logic?
    //Note that this method will insert at the end of the vector if insert_pos points past the end.

    vector<CirculationNode>::iterator it;

    int current_pos = 0;
    it = Circulation::begin();
    while(it != Circulation::end() && current_pos < insert_pos)
    {
        ++it;
        ++current_pos;
    }
    route.insert(it,node);

}
vector<Circulation::CirculationNode>::iterator Circulation::begin()
{
    return route.begin();
}
void Circulation::deleteNode(int index)
{
    //TODO: This probably is not the right logic.
    //Note that this deletes the last value if index points past the end.
    vector<CirculationNode>::iterator it;

    int current_pos = 0;
    it = Circulation::begin();
    while(it != Circulation::end() && current_pos < index)
    {
        ++it;
        ++current_pos;
    }
    route.erase(it);
}

vector<Circulation::CirculationNode>::iterator Circulation::end()
{
    return route.end();
}

Circulation::~Circulation()
{
    delete(&route);
}
