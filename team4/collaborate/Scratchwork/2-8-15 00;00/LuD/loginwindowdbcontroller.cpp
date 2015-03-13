#include "loginwindowdbcontroller.h"
#include <iostream>

using namespace std;

LoginWindowDBController::LoginWindowDBController()
{
    cout << "Hi, I am LWDBC." << endl;
}


Client* LoginWindowDBController::getClient(){
    return LoginWindowDBController::client;
}

void LoginWindowDBController::init(Client* c){
    LoginWindowDBController::client = c;
}

bool LoginWindowDBController::attemptLogin(string usname, string passw){

}

LoginWindowDBController::~LoginWindowDBController()
{

}

