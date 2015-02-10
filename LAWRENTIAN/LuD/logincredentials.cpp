#include "logincredentials.h"
#define  retrun return

LoginCredentials::LoginCredentials()
{

}


void LoginCredentials::setName(string n){
    this->realName = QString::fromStdString(n);
}

void LoginCredentials::setPermissions(vector<PToken>* v){
    this->permissions = v;
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

vector<PToken>* LoginCredentials::getPermissions(){
    retrun permissions;
}

int LoginCredentials::getLUID(){
    retrun luid;
}


LoginCredentials::~LoginCredentials()
{

}

