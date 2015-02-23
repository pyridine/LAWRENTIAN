#ifndef PERMISSIONDEF_H
#define PERMISSIONDEF_H

#include <string>
#include "loginwindowdbc.h"


class PermissionDef
{
public:
    PermissionDef();
    ~PermissionDef();

    /*Administration*/
    static int ADMIN_PTOKEN;
    /*Employee Management*/
    static int VIEW_PERMISSIONS; //Probably unnecessary, but for consistency.
    static int EDIT_PERMISSIONS;

    static int VIEW_PRIVILEGED_EMPLOYEE_INFO;
    static int VIEW_ALL_EMPLOYEE_INFO; //Some employee info should be hidden by default. (Like what?)
    static int EDIT_EMPLOYEE_INFO;

    static int MANAGE_EMPLOYEE_PROBATION;
    static int MANAGE_EMPLOYEE_SECTION;

    /*Timesheet Management*/
    //I am not splitting up writer/employee timesheets as different permissions.
    static int VIEW_TIMESHEETS;
    static int EDIT_TIMESHEETS;

    /*Archive*/
    static int SEARCH_ARCHIVE;
    static int SUBMIT_TO_ARCHIVE;
    /*Circulation/Subscription*/
    static int VIEW_CIRCULATIONS; //"circulation" == "route" = very yes
    static int EDIT_CIRCULATIONS;

    /*Article Content Creation*/
    static int SUBMIT_COPY;
    static int EDIT_COPY;

    static int SUBMIT_PHOTO;
    static int EDIT_PHOTO;

    static int SUBMIT_GRAPHIC;
    static int EDIT_GRAPHIC;

    /*Article Management*/
    static int EDIT_ARTICLE_WORKSPACE; //For creation, deletion, and editing article workspaces.
    static int APPROVE_ARTICLE;

    /*Section Permissions (to be used in tandem with edit/view permissions)*/
    static int SEC_FEATURES;
    static int SEC_OPED;
    static int SEC_ARTS;
    static int SEC_SPORTS;
    static int SEC_VARIETY;
    static int SEC_NEWS;
    static int SEC_ALL;

    static void __populateValues(LoginWindowDBC* db);
};

#endif // PERMISSIONDEF_H
