#include "sectiondef.h"

int SectionDef::NEWS_SECTION = -13;
int SectionDef::FEATURES_SECTION = -13;
int SectionDef::OPED_SECTION = -13;
int SectionDef::ARTSENT_SECTION = -13;
int SectionDef::SPORTS_SECTION = -13;
int SectionDef::VARIETY_SECTION = -13;

SectionDef::SectionDef()
{

}

SectionDef::~SectionDef()
{

}

void SectionDef::__populateValues(LoginWindowDBC *db){
    NEWS_SECTION = db->__getSectionID("NEWS_SECTION");
    FEATURES_SECTION = db->__getSectionID("FEATURES_SECTION");
    OPED_SECTION = db->__getSectionID("OPED_SECTION");
    ARTSENT_SECTION = db->__getSectionID("ARTSENT_SECTION");
    SPORTS_SECTION = db->__getSectionID("SPORTS_SECTION");
    VARIETY_SECTION = db->__getSectionID("VARIETY_SECTION");
}
