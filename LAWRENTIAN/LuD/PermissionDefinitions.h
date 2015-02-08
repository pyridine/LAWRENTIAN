#ifndef DEFINITIONS
#define DEFINITIONS

#include <stdlib.h>
#include <string>

using namespace std;

namespace PermissionDefinitions{

    //Basic Permissions
    enum PToken {
        /*Note the systematically defined names of all tokens and associated values*/

        /*Admin Priveleges (can do everything)*/
        ADMIN = 0,

        /*Ads*/
        VIEW_ADS = 1,
        EDIT_ADS = 2,

        /*Employee Management*/
        VIEW_PERMISSIONS = 3, //Probably unnecessary, but for consistency.
        EDIT_PERMISSIONS = 4,

        VIEW_EMPLOYEE_INFO = 5,
        VIEW_ALL_EMPLOYEE_INFO = 6, //Some employee info should be hidden by default. (Like what?)
        EDIT_EMPLOYEE_INFO = 7,

        /*Timesheet Management*/
        //I am not splitting up writer/employee timesheets as different permissions.
        VIEW_TIMESHEETS = 8,
        EDIT_TIMESHEETS = 9,

        /*Archive*/
        SEARCH_ARCHIVE = 10,
        SUBMIT_TO_ARCHIVE = 11,

        /*Circulation/Subscription*/
        VIEW_SUBSCRIPTIONS = 12,
        EDIT_SUBSCRIPTIONS = 13,
        VIEW_CIRCULATIONS = 14, //"circulation" == "route" = very yes
        EDIT_CIRCULATIONS = 15,

        /*Article Content Creation*/
        SUBMIT_COPY = 16,
        EDIT_COPY = 17,

        SUBMIT_PHOTO = 18,
        EDIT_PHOTO = 19,

        SUMBIT_GRAPHIC = 20,
        EDIT_GRAPHIC = 21,

        /*Article Management*/
        EDIT_ARTICLE_WORKSPACE = 22, //For creation, deletion, and editing article workspaces.

        /*Idea Management*/
        VIEW_IDEAS = 23,
        EDIT_IDEAS = 24,
        //Submitting ideas requires EDIT_ARTICLE_WORKSPACE permission.

        /*Section Permissions (to be used in tandem with edit/view permissions)*/
        SEC_FEATURES = 25,
        SEC_OPED = 26,
        SEC_ARTS = 27,
        SEC_SPORTS = 28,
        SEC_VARIETY = 29,
    };

    string translate(PToken a){
        switch(a){
            case ADMIN:
                return "Admin";
            case VIEW_ADS:
                return "View Ads";
            case EDIT_ADS:
                return "Edit Ads";
            case VIEW_PERMISSIONS:
                return "View Permissions";
            case EDIT_PERMISSIONS:
                return "View Permissions";
            case VIEW_EMPLOYEE_INFO:
                return "View Public Employee Information";
            case VIEW_ALL_EMPLOYEE_INFO:
                return "View Protected Employee Information";
            case EDIT_EMPLOYEE_INFO:
                return "Edit Employee Information";
            case VIEW_TIMESHEETS:
                return "View Timesheets";
            case EDIT_TIMESHEETS:
                return "Edit Timesheets";
            case SEARCH_ARCHIVE:
                return "Search the Archive";
            case SUBMIT_TO_ARCHIVE:
                return "Submit Issue to Archive";
            case VIEW_SUBSCRIPTIONS:
                return "View Subscriptions";
            case EDIT_SUBSCRIPTIONS:
                return "Edit Subscriptions";
            case VIEW_CIRCULATIONS:
                return "View Circulation Information";
            case EDIT_CIRCULATIONS:
                return "Edit Circulation Information";
            case SUBMIT_COPY:
                return "Submit Article Copy";
            case EDIT_COPY:
                return "Edit Article Copy";
            case SUBMIT_PHOTO:
                return "Submit Photos";
            case EDIT_PHOTO:
                return "Edit Photos";
            case: SUBMIT_GRAPHIC:
                return "Submit Illustrations";
            case: EDIT_GRAPHIC:
                return "Submit Illustrations";
            case: EDIT_ARTICLE_WORKSPACE:
                return "Create/Edit Article Workspaces";
            case: VIEW_IDEAS:
                return "View Ideas";
            case: EDIT_IDEAS:
                return "Edit Ideas";
            case: SEC_FEATURES:
                return "Features Section";
            case: SEC_OPED:
                return "Opinions & Editorials Section";
            case: SEC_ARTS:
                return "Arts Section";
            case: SEC_SPORTS:
                return "Sports Section";
            case: SEC_VARIETY:
                return "Variety Section";
            default:
                return "ERROR :(";
        }
    }
};

#endif // DEFINITIONS
