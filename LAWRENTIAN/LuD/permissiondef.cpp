#include "permissiondef.h"


// -13 implies value is not set. The true values are obtained from the database.
/*Administration*/
int PermissionDef::ADMIN_PTOKEN = -13;
/*Employee Management*/
int PermissionDef::VIEW_PERMISSIONS = -13; //Probably unnecessary, but for consistency.
int PermissionDef::EDIT_PERMISSIONS = -13;

int PermissionDef::VIEW_PRIVILEGED_EMPLOYEE_INFO = -13;
int PermissionDef::VIEW_ALL_EMPLOYEE_INFO = -13; //Some employee info should be hidden by default. (Like what?)
int PermissionDef::EDIT_EMPLOYEE_INFO = -13;

int PermissionDef::MANAGE_EMPLOYEE_PROBATION = -13;
int PermissionDef::MANAGE_EMPLOYEE_SECTION = -13;

/*Timesheet Management*/
//I am not splitting up writer/employee timesheets as different permissions.
int PermissionDef::VIEW_TIMESHEETS = -13;
int PermissionDef::EDIT_TIMESHEETS = -13;

/*Archive*/
int PermissionDef::SEARCH_ARCHIVE = -13;
int PermissionDef::SUBMIT_TO_ARCHIVE = -13;
/*Circulation/Subscription*/
int PermissionDef::VIEW_CIRCULATIONS = -13; //"circulation" == "route" = very yes
int PermissionDef::EDIT_CIRCULATIONS = -13;

/*Article Content Creation*/
int PermissionDef::SUBMIT_COPY = -13;
int PermissionDef::EDIT_COPY = -13;

int PermissionDef::SUBMIT_PHOTO = -13;
int PermissionDef::EDIT_PHOTO = -13;

int PermissionDef::SUBMIT_GRAPHIC = -13;
int PermissionDef::EDIT_GRAPHIC = -13;

/*Article Management*/
int PermissionDef::EDIT_ARTICLE_WORKSPACE = -13; //For creation, deletion, and editing article workspaces.
int PermissionDef::APPROVE_ARTICLE = -13;

/*Section Permissions (to be used in tandem with edit/view permissions)*/
int PermissionDef::SEC_FEATURES = -13;
int PermissionDef::SEC_OPED = -13;
int PermissionDef::SEC_ARTS = -13;
int PermissionDef::SEC_SPORTS = -13;
int PermissionDef::SEC_VARIETY = -13;
int PermissionDef::SEC_NEWS = -13;
int PermissionDef::SEC_ALL = -13;

PermissionDef::PermissionDef()
{

}

PermissionDef::~PermissionDef()
{

}

void PermissionDef::__populateValues(LoginWindowDBC* db){
    ADMIN_PTOKEN = db->__getPermissionID("ADMIN_PTOKEN");//
    VIEW_PERMISSIONS  = db->__getPermissionID("VIEW_PERMISSIONS");//

    VIEW_PRIVILEGED_EMPLOYEE_INFO  = db->__getPermissionID("VIEW_PRIVILEGED_EMPLOYEE_INFO");//
    VIEW_ALL_EMPLOYEE_INFO  = db->__getPermissionID("VIEW_ALL_EMPLOYEE_INFO");//
    EDIT_EMPLOYEE_INFO  = db->__getPermissionID("EDIT_EMPLOYEE_INFO");//
    MANAGE_EMPLOYEE_PROBATION  = db->__getPermissionID("MANAGE_EMPLOYEE_PROBATION");//
    MANAGE_EMPLOYEE_SECTION  = db->__getPermissionID("MANAGE_EMPLOYEE_SECTION");//

    VIEW_TIMESHEETS  = db->__getPermissionID("VIEW_TIMESHEETS");//
    EDIT_TIMESHEETS  = db->__getPermissionID("EDIT_TIMESHEETS");//

    SEARCH_ARCHIVE  = db->__getPermissionID("SEARCH_ARCHIVE");//
    SUBMIT_TO_ARCHIVE  = db->__getPermissionID("SUBMIT_TO_ARCHIVE");//

    VIEW_CIRCULATIONS  = db->__getPermissionID("VIEW_CIRCULATIONS");//
    EDIT_CIRCULATIONS  = db->__getPermissionID("EDIT_CIRCULATIONS");//
    SUBMIT_COPY  = db->__getPermissionID("SUBMIT_COPY");//
    EDIT_COPY  = db->__getPermissionID("EDIT_COPY");//
    SUBMIT_PHOTO  = db->__getPermissionID("SUBMIT_PHOTO");//
    EDIT_PHOTO  = db->__getPermissionID("EDIT_PHOTO");//
    SUBMIT_GRAPHIC  = db->__getPermissionID("SUBMIT_GRAPHIC");//
    EDIT_GRAPHIC  = db->__getPermissionID("EDIT_GRAPHIC");//
    EDIT_ARTICLE_WORKSPACE  = db->__getPermissionID("EDIT_ARTICLE_WORKSPACE");//
    APPROVE_ARTICLE  = db->__getPermissionID("APPROVE_ARTICLE");//

    SEC_FEATURES  = db->__getPermissionID("SEC_FEATURES");//
    SEC_OPED  = db->__getPermissionID("SEC_OPED");//
    SEC_ARTS  = db->__getPermissionID("SEC_ARTS");//
    SEC_SPORTS  = db->__getPermissionID("SEC_SPORTS");//
    SEC_VARIETY  = db->__getPermissionID("SEC_VARIETY");//
    SEC_NEWS  = db->__getPermissionID("SEC_NEWS");//
    SEC_ALL  = db->__getPermissionID("SEC_ALL");//

}
