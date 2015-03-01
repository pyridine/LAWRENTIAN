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

     LocationDef::VOLUNTEER_CENTER = db->__getLocationID("VOLUNTEER_CENTER");
     LocationDef::RAYMOND_HOUSE= db->__getLocationID("RAYMOND_HOUSE");
     LocationDef::BRIGGS_SACS= db->__getLocationID("BRIGGS_SACS");
     LocationDef::BRIGGS_LOB= db->__getLocationID("BRIGGS_LOB");
     LocationDef::BRIGGS_FAC= db->__getLocationID("BRIGGS_FAC");
     LocationDef::DIVERSITY= db->__getLocationID("DIVERSITY");
     LocationDef::VIKING_ROOM= db->__getLocationID("VIKING_ROOM");
     LocationDef::SAMPSON= db->__getLocationID("SAMPSON");
     LocationDef::LIBARY= db->__getLocationID("LIBARY");
     LocationDef::WRISTON_FAC= db->__getLocationID("WRISTON_FAC");
     LocationDef::HURVIS_FRONT= db->__getLocationID("HURVIS_FRONT");
     LocationDef::HURVIS_CAREER= db->__getLocationID("HURVIS_CAREER");
     LocationDef::HURVIS_LEFT= db->__getLocationID("HURVIS_LEFT");
     LocationDef::SAGE = db->__getLocationID("SAGE");
     LocationDef::COLMAN= db->__getLocationID("COLMAN");
     LocationDef::KOHLER= db->__getLocationID("KOHLER");
     LocationDef::TREVER= db->__getLocationID("TREVER");
     LocationDef::ORMSBY_WORMSBY= db->__getLocationID("ORMSBY_WORMSBY");
     LocationDef::HIETT= db->__getLocationID("HIETT");
     LocationDef::PLANTZ= db->__getLocationID("PLANTZ");
     LocationDef::DELT= db->__getLocationID("DELT");
     LocationDef::DRAHEIM= db->__getLocationID("DRAHEIM");
     LocationDef::SWING= db->__getLocationID("SWING");
     LocationDef::GAMING= db->__getLocationID("GAMING");
     LocationDef::BETA= db->__getLocationID("BETA");
     LocationDef::SANKOFA= db->__getLocationID("SANKOFA");
     LocationDef::GREENFIRE= db->__getLocationID("GREENFIRE");
     LocationDef::ORC= db->__getLocationID("ORC");
     LocationDef::BIG_EXEC= db->__getLocationID("BIG_EXEC");
     LocationDef::SMALL_EXEC= db->__getLocationID("SMALL_EXEC");
     LocationDef::WELLNESS_FRONT= db->__getLocationID("WELLNESS_FRONT");
     LocationDef::SLUG= db->__getLocationID("SLUG");
}

