#include "permissions.h"
#include "PermissionDefinitions.h" //TODO: Should probably IFNDEF this.
#include "titledefinitions.h"

#include <vector>
#include <string>


using namespace PermissionDefinitions;
using namespace TitleDefinitions;
using namespace std;

Permissions::Permissions(vector<PToken> *p)
{
    perms = p;
}
Permissions::Permissions(){

}

bool Permissions::hasPermission(PToken query){
    vector<PToken>::iterator it;

    for(it = perms->begin(); it != perms->end(); ++it){
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
    case ADMIN_PTOKEN:
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
    case SEC_NEWS:
        return "Variety Section";
    case APPROVE_ARTICLE:
        return "Approve Article";
    case MANAGE_EMPLOYEE_PROBATION:
        return "Manage Probation";
    case MANAGE_EMPLOYEE_SECTION:
        return "Assign/Unassign Section";
    default:
        return "ERROR T_T";
    }

}

string Permissions::translateTitle(Title t){

    switch(t){
    case ADMIN_TITLE:
        return "Administrator";
    case EDITOR_IN_CHIEF:
        return "Editor in Chief";
    case COPY_CHIEF:
        return "Copy Chief";
    case BUSINESS_MANAGER:
        return "Business Manager";
    case MANAGING_EDITOR:
        return "Managing Editor";
    case NEWS_EDITOR :
        return "News Editor";
    case ASSOCIATE_NEWS_EDITOR :
        return "Associate News Editor";
    case FEATURES_EDITOR :
        return "Features Editor";
    case OPED_EDITOR :
        return "OE Editor";
    case ARTS_AND_ENT_EDITOR :
        return "A&E Timesheets";
    case SPORTS_EDITOR :
        return "Sports Editor";
    case VARIETY_EDITOR :
        return "Variety Editor";
    case PHOTO_EDITOR :
        return "Photo Editor";
    case STAFF_ARTIST :
        return "Staff Artist";
    case WEB_MANAGER :
        return "Web Manager";
    case COPY_EDITOR :
        return "Copy Editor";
    case CIRCULATION_MANAGER :
        return "Circulation Manager";
    case SUBSCRIPTION_MANAGER :
        return "Subscription Manager";
    case WRITER :
        return "Lowly Writer :(";
    case PHOTOGRAPHER :
        return "Lowly Photographer :(";
    default:
        return "ERROR T_T";
    }
}

//TODO: finish this method
vector<PToken>* Permissions::__DEBUG_GET_PERMISSION_LIST_FOR_TITLE(Title t){
    vector<PToken> permz;

    switch(t){
    case ADMIN_TITLE:
        permz.push_back(ADMIN_PTOKEN);
        break;
    case EDITOR_IN_CHIEF:
        permz.push_back(SUBMIT_TO_ARCHIVE);
        permz.push_back(VIEW_ADS);
        permz.push_back(VIEW_CIRCULATIONS);
        permz.push_back(VIEW_PERMISSIONS);
        permz.push_back(VIEW_SUBSCRIPTIONS);
        permz.push_back(VIEW_TIMESHEETS);
        permz.push_back(VIEW_IDEAS);
        permz.push_back(SEC_FEATURES);
        permz.push_back(SEC_NEWS);
        permz.push_back(SEC_OPED);
        permz.push_back(SEC_ARTS);
        permz.push_back(SEC_SPORTS);
        permz.push_back(SEC_VARIETY);
        permz.push_back(VIEW_PERMISSIONS);
        permz.push_back(EDIT_PERMISSIONS);
        break;
    case COPY_CHIEF:
        permz.push_back(EDIT_COPY);
        permz.push_back(SEC_FEATURES);
        permz.push_back(SEC_NEWS);
        permz.push_back(SEC_OPED);
        permz.push_back(SEC_ARTS);
        permz.push_back(SEC_SPORTS);
        permz.push_back(SEC_VARIETY);
        break;
    case BUSINESS_MANAGER:
        permz.push_back(VIEW_ADS);
        permz.push_back(EDIT_ADS);
        break;
    case MANAGING_EDITOR:
        permz.push_back(VIEW_ALL_EMPLOYEE_INFO);
        permz.push_back(EDIT_EMPLOYEE_INFO);
        permz.push_back(EDIT_TIMESHEETS);
        permz.push_back(VIEW_TIMESHEETS);
        break;
    case NEWS_EDITOR :
        permz.push_back(EDIT_ARTICLE_WORKSPACE);
        permz.push_back(EDIT_COPY);
        permz.push_back(SEC_NEWS);
        permz.push_back(MANAGE_EMPLOYEE_PROBATION);
        permz.push_back(MANAGE_EMPLOYEE_SECTION);
        break;
    case ASSOCIATE_NEWS_EDITOR :
        permz.push_back(EDIT_ARTICLE_WORKSPACE);
        permz.push_back(EDIT_COPY);
        permz.push_back(SEC_NEWS);
        permz.push_back(MANAGE_EMPLOYEE_PROBATION);
        permz.push_back(MANAGE_EMPLOYEE_SECTION);
        break;
    case FEATURES_EDITOR :
        permz.push_back(EDIT_ARTICLE_WORKSPACE);
        permz.push_back(EDIT_COPY);
        permz.push_back(SEC_FEATURES);
        permz.push_back(MANAGE_EMPLOYEE_PROBATION);
        permz.push_back(MANAGE_EMPLOYEE_SECTION);
        break;
    case OPED_EDITOR :
        permz.push_back(EDIT_ARTICLE_WORKSPACE);
        permz.push_back(EDIT_COPY);
        permz.push_back(SEC_OPED);
        permz.push_back(MANAGE_EMPLOYEE_PROBATION);
        permz.push_back(MANAGE_EMPLOYEE_SECTION);
        break;
    case ARTS_AND_ENT_EDITOR :
        permz.push_back(EDIT_ARTICLE_WORKSPACE);
        permz.push_back(EDIT_COPY);
        permz.push_back(SEC_ARTS);
        permz.push_back(MANAGE_EMPLOYEE_PROBATION);
        permz.push_back(MANAGE_EMPLOYEE_SECTION);
        break;
    case SPORTS_EDITOR :
        permz.push_back(EDIT_ARTICLE_WORKSPACE);
        permz.push_back(EDIT_COPY);
        permz.push_back(SEC_SPORTS);
        permz.push_back(MANAGE_EMPLOYEE_PROBATION);
        permz.push_back(MANAGE_EMPLOYEE_SECTION);
        break;
    case VARIETY_EDITOR :
        permz.push_back(EDIT_ARTICLE_WORKSPACE);
        permz.push_back(EDIT_COPY);
        permz.push_back(SEC_VARIETY);
        permz.push_back(MANAGE_EMPLOYEE_PROBATION);
        permz.push_back(MANAGE_EMPLOYEE_SECTION);
        break;
    case PHOTO_EDITOR :
        permz.push_back(SUBMIT_PHOTO);
        permz.push_back(EDIT_PHOTO);
        permz.push_back(SEC_FEATURES);
        permz.push_back(SEC_NEWS);
        permz.push_back(SEC_OPED);
        permz.push_back(SEC_ARTS);
        permz.push_back(SEC_SPORTS);
        permz.push_back(SEC_VARIETY);
        break;
    case STAFF_ARTIST :
        permz.push_back(SUBMIT_GRAPHIC);
        permz.push_back(EDIT_GRAPHIC);
        permz.push_back(SEC_FEATURES);
        permz.push_back(SEC_OPED);
        permz.push_back(SEC_ARTS);
        permz.push_back(SEC_NEWS);
        permz.push_back(SEC_SPORTS);
        permz.push_back(SEC_VARIETY);
        break;
    case WEB_MANAGER :
        break;
    case COPY_EDITOR :
        permz.push_back(EDIT_COPY);
        permz.push_back(SEC_NEWS);
        permz.push_back(SEC_FEATURES);
        permz.push_back(SEC_OPED);
        permz.push_back(SEC_ARTS);
        permz.push_back(SEC_SPORTS);
        permz.push_back(SEC_VARIETY);
        break;
    case CIRCULATION_MANAGER :
        permz.push_back(EDIT_CIRCULATIONS);
        permz.push_back(VIEW_CIRCULATIONS);
        break;
    case SUBSCRIPTION_MANAGER :
        permz.push_back(EDIT_SUBSCRIPTIONS);
        permz.push_back(VIEW_SUBSCRIPTIONS);
        break;
    case WRITER :
        //Remember, the manager will have to manually set their section.
        permz.push_back(SUBMIT_COPY);
        break;
    case PHOTOGRAPHER :
        //Remember, the manager will have to manually set their section.
        permz.push_back(SUBMIT_PHOTO);
        break;
    default:
        break;
}
    return &permz;

}
