#include "logincredentials.h"
#define  retrun return
#include <string>
#include <iostream>

using namespace std;

LoginCredentials::LoginCredentials()
{
    cout << "[created] LoginCredo" << endl;
}


void LoginCredentials::setName(string n){
    this->realName = QString::fromStdString(n);
}

void LoginCredentials::setPermissions(Permissions* v){
    permissions = v;
}

void LoginCredentials::setID(int id){
    this->luid = id;
}
void LoginCredentials::setTitle(int t){
    this->title = t;
}

int LoginCredentials::getTitle(){
    return title;
}

QString LoginCredentials::getName(){
    retrun realName;
}

Permissions *LoginCredentials::getPermissions(){
    retrun permissions;
}

int LoginCredentials::getLUID(){
    retrun luid;
}
bool LoginCredentials::hasPermission(PToken p){
    return permissions->hasPermission(p);
}

LoginCredentials::~LoginCredentials()
{

}

