#include "locationdef.h"

int LocationDef::VOLUNTEER_CENTER = -13;
int LocationDef::RAYMOND_HOUSE = -13;
int LocationDef::BRIGGS_SACS = -13;
int LocationDef::BRIGGS_LOB = -13;
int LocationDef::BRIGGS_FAC = -13;
int LocationDef::DIVERSITY = -13;
int LocationDef::VIKING_ROOM = -13;
int LocationDef::SAMPSON = -13;
int LocationDef::LIBARY = -13;
int LocationDef::WRISTON_FAC = -13;
int LocationDef::HURVIS_FRONT = -13;
int LocationDef::HURVIS_CAREER = -13;
int LocationDef::HURVIS_LEFT = -13;
int LocationDef::SAGE = -13;
int LocationDef::COLMAN = -13;
int LocationDef::KOHLER = -13;
int LocationDef::TREVER = -13;
int LocationDef::ORMSBY_WORMSBY = -13;
int LocationDef::HIETT = -13;
int LocationDef::PLANTZ = -13;
int LocationDef::DELT = -13;
int LocationDef::DRAHEIM = -13;
int LocationDef::SWING = -13;
int LocationDef::GAMING = -13;
int LocationDef::BETA = -13;
int LocationDef::SANKOFA = -13;
int LocationDef::GREENFIRE = -13;
int LocationDef::ORC = -13;
int LocationDef::BIG_EXEC = -13;
int LocationDef::SMALL_EXEC = -13;
int LocationDef::WELLNESS_FRONT = -13;
int LocationDef::SLUG = -13;

LocationDef::LocationDef()
{

}

LocationDef::~LocationDef()
{

}

void LocationDef::__populateValues(LoginWindowDBC *db){

     VOLUNTEER_CENTER = db->__getLocationID("VOLUNTEER_CENTER");
     RAYMOND_HOUSE= db->__getLocationID("RAYMOND_HOUSE");
     BRIGGS_SACS= db->__getLocationID("BRIGGS_SACS");
     BRIGGS_LOB= db->__getLocationID("BRIGGS_LOB");
     BRIGGS_FAC= db->__getLocationID("BRIGGS_FAC");
     DIVERSITY= db->__getLocationID("DIVERSITY");
     VIKING_ROOM= db->__getLocationID("VIKING_ROOM");
     SAMPSON= db->__getLocationID("SAMPSON");
     LIBARY= db->__getLocationID("LIBARY");
     WRISTON_FAC= db->__getLocationID("WRISTON_FAC");
     HURVIS_FRONT= db->__getLocationID("HURVIS_FRONT");
     HURVIS_CAREER= db->__getLocationID("HURVIS_CAREER");
     HURVIS_LEFT= db->__getLocationID("HURVIS_LEFT");
     SAGE = db->__getLocationID("SAGE");
     COLMAN= db->__getLocationID("COLMAN");
     KOHLER= db->__getLocationID("KOHLER");
     TREVER= db->__getLocationID("TREVER");
     ORMSBY_WORMSBY= db->__getLocationID("ORMSBY_WORMSBY");
     HIETT= db->__getLocationID("HIETT");
     PLANTZ= db->__getLocationID("PLANTZ");
     DELT= db->__getLocationID("DELT");
     DRAHEIM= db->__getLocationID("DRAHEIM");
     SWING= db->__getLocationID("SWING");
     GAMING= db->__getLocationID("GAMING");
     BETA= db->__getLocationID("BETA");
     SANKOFA= db->__getLocationID("SANKOFA");
     GREENFIRE= db->__getLocationID("GREENFIRE");
     ORC= db->__getLocationID("ORC");
     BIG_EXEC= db->__getLocationID("BIG_EXEC");
     SMALL_EXEC= db->__getLocationID("SMALL_EXEC");
     WELLNESS_FRONT= db->__getLocationID("WELLNESS_FRONT");
     SLUG= db->__getLocationID("SLUG");
}

