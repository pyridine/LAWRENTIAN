#ifndef LOCATIONDEF_H
#define LOCATIONDEF_H
#include "loginwindowdbc.h"

class LocationDef
{


public:
    LocationDef();
    ~LocationDef();

    vector<int> locationIds;

    static int VOLUNTEER_CENTER;
    static int RAYMOND_HOUSE;
    static int BRIGGS_SACS;
    static int BRIGGS_LOB;
    static int BRIGGS_FAC;
    static int DIVERSITY;
    static int VIKING_ROOM;
    static int SAMPSON;
    static int LIBARY;
    static int WRISTON_FAC;
    static int HURVIS_FRONT;
    static int HURVIS_CAREER;
    static int HURVIS_LEFT;
    static int SAGE;
    static int COLMAN;
    static int KOHLER;
    static int TREVER;
    static int ORMSBY_WORMSBY;
    static int HIETT;
    static int PLANTZ;
    static int DELT;
    static int DRAHEIM;
    static int SWING;
    static int GAMING;
    static int BETA;
    static int SANKOFA;
    static int GREENFIRE;
    static int ORC;
    static int BIG_EXEC;
    static int SMALL_EXEC;
    static int WELLNESS_FRONT;
    static int SLUG;

    static void __populateValues(LoginWindowDBC* db);
};

#endif // LOCATIONDEF_H
