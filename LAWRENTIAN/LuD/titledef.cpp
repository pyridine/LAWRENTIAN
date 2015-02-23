#include "titledef.h"
//Can do everything.
int TitleDef::ADMIN_TITLE = -14;
int TitleDef::EDITOR_IN_CHIEF = -14;
int TitleDef::COPY_CHIEF = -14;
int TitleDef::BUSINESS_MANAGER = -14;
int TitleDef::MANAGING_EDITOR = -14;
int TitleDef::NEWS_EDITOR = -14;
int TitleDef::ASSOCIATE_NEWS_EDITOR = -14;
int TitleDef::FEATURES_EDITOR = -14;
int TitleDef::OPED_EDITOR = -14;
int TitleDef::ARTS_AND_ENT_EDITOR = -14;
int TitleDef::SPORTS_EDITOR = -14;
int TitleDef::VARIETY_EDITOR = -14;
int TitleDef::PHOTO_EDITOR = -14;
int TitleDef::STAFF_ARTIST = -14;
int TitleDef::WEB_MANAGER = -14;
int TitleDef::COPY_EDITOR = -14;
int TitleDef::CIRCULATION_MANAGER = -14;
int TitleDef::SUBSCRIPTION_MANAGER = -14;
int TitleDef::WRITER = -14;
int TitleDef::PHOTOGRAPHER = -14;
int TitleDef::NO_TITLE = -14;

TitleDef::TitleDef()
{

}

TitleDef::~TitleDef()
{

}

void TitleDef::__populateValues(LoginWindowDBC *db){
    ADMIN_TITLE = db->__getTitleID("ADMIN_TITLE");
    NO_TITLE = db->__getTitleID("NO_TITLE");
    EDITOR_IN_CHIEF = db->__getTitleID("EDITOR_IN_CHIEF");
    COPY_CHIEF = db->__getTitleID("COPY_CHIEF");
    BUSINESS_MANAGER = db->__getTitleID("BUSINESS_MANAGER");
    MANAGING_EDITOR = db->__getTitleID("MANAGING_EDITOR");
    NEWS_EDITOR = db->__getTitleID("NEWS_EDITOR");
    ASSOCIATE_NEWS_EDITOR = db->__getTitleID("ASSOCIATE_NEWS_EDITOR");
    FEATURES_EDITOR = db->__getTitleID("FEATURES_EDITOR");
    OPED_EDITOR = db->__getTitleID("OPED_EDITOR");
    ARTS_AND_ENT_EDITOR = db->__getTitleID("ARTS_AND_ENT_EDITOR");
    SPORTS_EDITOR = db->__getTitleID("SPORTS_EDITOR");
    VARIETY_EDITOR = db->__getTitleID("VARIETY_EDITOR");
    PHOTO_EDITOR = db->__getTitleID("PHOTO_EDITOR");
    STAFF_ARTIST = db->__getTitleID("STAFF_ARTIST");
    WEB_MANAGER = db->__getTitleID("WEB_MANAGER");
    COPY_EDITOR = db->__getTitleID("COPY_EDITOR");
    CIRCULATION_MANAGER = db->__getTitleID("CIRCULATION_MANAGER");
    SUBSCRIPTION_MANAGER = db->__getTitleID("SUBSCRIPTION_MANAGER");
    WRITER = db->__getTitleID("WRITER");
    PHOTOGRAPHER = db->__getTitleID("PHOTOGRAPHER");
}
