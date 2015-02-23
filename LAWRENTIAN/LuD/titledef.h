#ifndef TITLEDEF_H
#define TITLEDEF_H

#include "loginwindowdbc.h"

class TitleDef
{
public:
    TitleDef();
    ~TitleDef();
    static int NO_TITLE;
    static int ADMIN_TITLE;
    static int EDITOR_IN_CHIEF;
    static int COPY_CHIEF ;
    static int BUSINESS_MANAGER ;
    static int MANAGING_EDITOR ;
    static int NEWS_EDITOR ;
    static int ASSOCIATE_NEWS_EDITOR ;
    static int FEATURES_EDITOR ;
    static int OPED_EDITOR ;
    static int ARTS_AND_ENT_EDITOR ;
    static int SPORTS_EDITOR ;
    static int VARIETY_EDITOR ;
    static int PHOTO_EDITOR ;
    static int STAFF_ARTIST ;
    static int WEB_MANAGER ;
    static int COPY_EDITOR ;
    static int CIRCULATION_MANAGER ;
    static int SUBSCRIPTION_MANAGER ;
    static int WRITER ;
    static int PHOTOGRAPHER ;

    static void __populateValues(LoginWindowDBC* db);
};

#endif // TITLEDEF_H
