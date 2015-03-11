#ifndef DATABASECONTROLLER
#define DATABASECONTROLLER
#include "client.h"

using namespace std;

namespace df
{
    const QString dbFormat = "yyyy-MM-dd";
    const QString srvrFormat = "dd MMM yyyy";
}

class DatabaseController{
public:
    DatabaseController(Client* c);
    Client* getClient();

    string translateTitle(int titleID);
    string translatePermission(int permID);
    string translateLocation(int locID);
    string translateSection(int secID);
    string translateRoute(int rID);


protected:
    Client* client;
    void executeSQLString(QString sql);
    void executeSQLString_Args(string sql,vector<string>* bindNames,vector<QVariant>* bindList);
    vector<int> *execute_int_for_intvect(string sql,string argname,int arg);
    vector<int> *execute_null_for_intvect(string sql);

};

#endif // DATABASECONTROLLER

