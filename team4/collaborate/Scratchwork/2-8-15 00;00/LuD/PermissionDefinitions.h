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

        SUBMIT_GRAPHIC = 20,
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
            case PToken::ADMIN:
                return "Admin";
            case PToken::VIEW_ADS:
                return "View Ads";
            case PToken::EDIT_ADS:
                return "Edit Ads";
            case PToken::VIEW_PERMISSIONS:
                return "View Permissions";
            case PToken::EDIT_PERMISSIONS:
                return "View Permissions";
            case PToken::VIEW_EMPLOYEE_INFO:
                return "View Public Employee Information";
            case PToken::VIEW_ALL_EMPLOYEE_INFO:
                return "View Protected Employee Information";
            case PToken::EDIT_EMPLOYEE_INFO:
                return "Edit Employee Information";
            case PToken::VIEW_TIMESHEETS:
                return "View Timesheets";
            case PToken::EDIT_TIMESHEETS:
                return "Edit Timesheets";
            case PToken::SEARCH_ARCHIVE:
                return "Search the Archive";
            case PToken::SUBMIT_TO_ARCHIVE:
                return "Submit Issue to Archive";
            case PToken::VIEW_SUBSCRIPTIONS:
                return "View Subscriptions";
            case PToken::EDIT_SUBSCRIPTIONS:
                return "Edit Subscriptions";
            case PToken::VIEW_CIRCULATIONS:
                return "View Circulation Information";
            case PToken::EDIT_CIRCULATIONS:
                return "Edit Circulation Information";
            case PToken::SUBMIT_COPY:
                return "Submit Article Copy";
            case PToken::EDIT_COPY:
                return "Edit Article Copy";
            case PToken::SUBMIT_PHOTO:
                return "Submit Photos";
            case PToken::EDIT_PHOTO:
                return "Edit Photos";
            case PToken::SUBMIT_GRAPHIC:
                return "Submit Illustrations";
            case PToken::EDIT_GRAPHIC:
                return "Submit Illustrations";
            case PToken::EDIT_ARTICLE_WORKSPACE:
                return "Create/Edit Article Workspaces";
            case PToken::VIEW_IDEAS:
                return "View Ideas";
            case PToken::EDIT_IDEAS:
                return "Edit Ideas";
            case PToken::SEC_FEATURES:
                return "Features Section";
            case PToken::SEC_OPED:
                return "Opinions & Editorials Section";
            case PToken::SEC_ARTS:
                return "Arts Section";
            case PToken::SEC_SPORTS:
                return "Sports Section";
            case PToken::SEC_VARIETY:
                return "Variety Section";
            default:
                return "ERROR T_T";
        }
    }
};

#endif // DEFINITIONS
