#include "permissions.h"
#include "PermissionDefinitions.h" //TODO: Should probably IFNDEF this.

#include <vector>
#include <string>


using namespace PermissionDefinitions;
using namespace std;

Permissions::Permissions(vector<PToken> &p, int id)
{
    perms = p;
    LUID = id;
}

bool Permissions::hasPermission(PToken query){
    vector<PToken>::iterator it;

    for(it = perms.begin(); it != perms.end(); ++it){
        if((*it) == query){
            return true;
        }
    }
    return false;
}

Permissions::~Permissions()
{
    delete(&perms);
}

string Permissions::translatePermission(PermissionDefinitions::PToken p){

    switch(p){
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
    case SUBMIT_GRAPHIC:
            return "Submit Illustrations";
    case EDIT_GRAPHIC:
            return "Submit Illustrations";
    case EDIT_ARTICLE_WORKSPACE:
            return "Create/Edit Article Workspaces";
    case VIEW_IDEAS:
            return "View Ideas";
    case EDIT_IDEAS:
            return "Edit Ideas";
    case SEC_FEATURES:
            return "Features Section";
    case SEC_OPED:
            return "Opinions & Editorials Section";
    case SEC_ARTS:
            return "Arts Section";
    case SEC_SPORTS:
            return "Sports Section";
    case SEC_VARIETY:
            return "Variety Section";
    default:
        return "ERROR :(";
    }

}

