#include "permissions.h"
#include "permissiondef.h"
#include "titledef.h"
#include <vector>
#include <string>

using namespace std;

Permissions::Permissions(vector<int> *p)
{
    perms = p;
}
Permissions::Permissions(){

}

bool Permissions::hasPermission(int query){
    vector<int>::iterator it;

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


vector<int>* Permissions::__DEBUG_GET_PERMISSION_LIST_FOR_TITLE(int t){
    vector<int> *permz = new vector<int>;

    //Unfortunately, the title ints are not determined at compile time,
    //so we can't use a switch :(

    if (t == TitleDef::ADMIN_TITLE){
        permz->push_back(PermissionDef::ADMIN_PTOKEN);
    }
    if (t == TitleDef::EDITOR_IN_CHIEF){
        permz->push_back(PermissionDef::SUBMIT_TO_ARCHIVE);
        permz->push_back(PermissionDef::VIEW_CIRCULATIONS);
        permz->push_back(PermissionDef::VIEW_PERMISSIONS);
        permz->push_back(PermissionDef::VIEW_TIMESHEETS);
        permz->push_back(PermissionDef::SEC_FEATURES);
        permz->push_back(PermissionDef::SEC_NEWS);
        permz->push_back(PermissionDef::SEC_OPED);
        permz->push_back(PermissionDef::SEC_ARTS);
        permz->push_back(PermissionDef::SEC_SPORTS);
        permz->push_back(PermissionDef::SEC_VARIETY);
        permz->push_back(PermissionDef::VIEW_PERMISSIONS);
        permz->push_back(PermissionDef::EDIT_PERMISSIONS);
    }
    if (t == TitleDef::COPY_CHIEF){
        permz->push_back(PermissionDef::EDIT_COPY);
        permz->push_back(PermissionDef::SEC_FEATURES);
        permz->push_back(PermissionDef::SEC_NEWS);
        permz->push_back(PermissionDef::SEC_OPED);
        permz->push_back(PermissionDef::SEC_ARTS);
        permz->push_back(PermissionDef::SEC_SPORTS);
        permz->push_back(PermissionDef::SEC_VARIETY);
    }

    if (t == TitleDef::MANAGING_EDITOR){
        permz->push_back(PermissionDef::VIEW_ALL_EMPLOYEE_INFO);
        permz->push_back(PermissionDef::EDIT_EMPLOYEE_INFO);
        permz->push_back(PermissionDef::EDIT_TIMESHEETS);
        permz->push_back(PermissionDef::VIEW_TIMESHEETS);
    }
    if (t == TitleDef::NEWS_EDITOR ){
        permz->push_back(PermissionDef::EDIT_ARTICLE_WORKSPACE);
        permz->push_back(PermissionDef::EDIT_COPY);
        permz->push_back(PermissionDef::SEC_NEWS);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_PROBATION);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_SECTION);
    }
    if (t == TitleDef::ASSOCIATE_NEWS_EDITOR ){
        permz->push_back(PermissionDef::EDIT_ARTICLE_WORKSPACE);
        permz->push_back(PermissionDef::EDIT_COPY);
        permz->push_back(PermissionDef::SEC_NEWS);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_PROBATION);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_SECTION);
    }
    if (t == TitleDef::FEATURES_EDITOR ){
        permz->push_back(PermissionDef::EDIT_ARTICLE_WORKSPACE);
        permz->push_back(PermissionDef::EDIT_COPY);
        permz->push_back(PermissionDef::SEC_FEATURES);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_PROBATION);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_SECTION);
    }
    if (t == TitleDef::OPED_EDITOR ){
        permz->push_back(PermissionDef::EDIT_ARTICLE_WORKSPACE);
        permz->push_back(PermissionDef::EDIT_COPY);
        permz->push_back(PermissionDef::SEC_OPED);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_PROBATION);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_SECTION);
    }
    if (t == TitleDef::ARTS_AND_ENT_EDITOR ){
        permz->push_back(PermissionDef::EDIT_ARTICLE_WORKSPACE);
        permz->push_back(PermissionDef::EDIT_COPY);
        permz->push_back(PermissionDef::SEC_ARTS);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_PROBATION);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_SECTION);
    }
    if (t == TitleDef::SPORTS_EDITOR ){
        permz->push_back(PermissionDef::EDIT_ARTICLE_WORKSPACE);
        permz->push_back(PermissionDef::EDIT_COPY);
        permz->push_back(PermissionDef::SEC_SPORTS);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_PROBATION);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_SECTION);
    }
    if (t == TitleDef::VARIETY_EDITOR ){
        permz->push_back(PermissionDef::EDIT_ARTICLE_WORKSPACE);
        permz->push_back(PermissionDef::EDIT_COPY);
        permz->push_back(PermissionDef::SEC_VARIETY);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_PROBATION);
        permz->push_back(PermissionDef::MANAGE_EMPLOYEE_SECTION);
    }
    if (t == TitleDef::PHOTO_EDITOR ){
        permz->push_back(PermissionDef::SUBMIT_PHOTO);
        permz->push_back(PermissionDef::EDIT_PHOTO);
        permz->push_back(PermissionDef::SEC_FEATURES);
        permz->push_back(PermissionDef::SEC_NEWS);
        permz->push_back(PermissionDef::SEC_OPED);
        permz->push_back(PermissionDef::SEC_ARTS);
        permz->push_back(PermissionDef::SEC_SPORTS);
        permz->push_back(PermissionDef::SEC_VARIETY);
    }
    if (t == TitleDef::STAFF_ARTIST ){
        permz->push_back(PermissionDef::SUBMIT_GRAPHIC);
        permz->push_back(PermissionDef::EDIT_GRAPHIC);
        permz->push_back(PermissionDef::SEC_FEATURES);
        permz->push_back(PermissionDef::SEC_OPED);
        permz->push_back(PermissionDef::SEC_ARTS);
        permz->push_back(PermissionDef::SEC_NEWS);
        permz->push_back(PermissionDef::SEC_SPORTS);
        permz->push_back(PermissionDef::SEC_VARIETY);
    }
    if (t == TitleDef::WEB_MANAGER ){
    }
    if (t == TitleDef::COPY_EDITOR ){
        permz->push_back(PermissionDef::EDIT_COPY);
        permz->push_back(PermissionDef::SEC_NEWS);
        permz->push_back(PermissionDef::SEC_FEATURES);
        permz->push_back(PermissionDef::SEC_OPED);
        permz->push_back(PermissionDef::SEC_ARTS);
        permz->push_back(PermissionDef::SEC_SPORTS);
        permz->push_back(PermissionDef::SEC_VARIETY);
    }
    if (t == TitleDef::CIRCULATION_MANAGER ){
        permz->push_back(PermissionDef::EDIT_CIRCULATIONS);
        permz->push_back(PermissionDef::VIEW_CIRCULATIONS);
    }

    if (t == TitleDef::WRITER ){
        //Remember, the manager will have to manually set their section...
        permz->push_back(PermissionDef::SUBMIT_COPY);
    }
    if (t == TitleDef::PHOTOGRAPHER ){
        //Remember, the manager will have to manually set their section...
        permz->push_back(PermissionDef::SUBMIT_PHOTO);
    }


    return permz;

}
