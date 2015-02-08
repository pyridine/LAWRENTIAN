#include "logincredentials.h"

LoginCredentials::LoginCredentials(string& sn, string& ttl, Permissions *p, int id)
{
    LoginCredentials::username = sn;
    LoginCredentials::title = ttl;
    LoginCredentials::permissions = p;
    LoginCredentials::luid = id;

}

LoginCredentials::~LoginCredentials()
{

}

