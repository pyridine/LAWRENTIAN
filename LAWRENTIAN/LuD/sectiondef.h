#ifndef SECTIONDEF_H
#define SECTIONDEF_H

#include "loginwindowdbc.h"

class SectionDef
{
public:
    SectionDef();
    ~SectionDef();

    static int NEWS_SECTION;
    static int FEATURES_SECTION;
    static int OPED_SECTION;
    static int ARTSENT_SECTION;
    static int SPORTS_SECTION;
    static int VARIETY_SECTION;

    static void __populateValues(LoginWindowDBC* db);
};

#endif // SECTIONDEF_H
