#include "editroutewindowdbc.h"
#include <utility>
#include <iostream>
#include "route.h"

using std::vector;
using std::string;
using namespace std;
namespace ERWDBCCommands{
     const string GETALLLOCNUMS = "SELECT idlocation from lawrentian.location ORDER BY idlocation ASC";
     const string DROP_ROUTE = "DELETE FROM lawrentian.routes WHERE routeid = :id";
     const string INSERT_ROUTE_POINT = "INSERT INTO lawrentian.routes (routeid,idlocation,numberOfIssues,locationorder) VALUES (:id,:loc,:num,:ord)";
     const string DEL_ROUTENAME = "DELETE FROM lawrentian.routenames WHERE routeID = :id";
     const string ADD_ROUTENAME = "INSERT INTO lawrentian.routenames (routeID,routename) VALUES (:id,:narm)";
}
using namespace ERWDBCCommands;
EditRouteWindowDBC::EditRouteWindowDBC(Client* c):DatabaseController(c)
{

}

EditRouteWindowDBC::~EditRouteWindowDBC()
{

}

vector<int>* EditRouteWindowDBC::getAllLocationIDs(){
    vector<int>* Ticking_Away = new vector<int>;

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GETALLLOCNUMS));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            Ticking_Away->push_back(result->value(0).toInt());
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return Ticking_Away;
}


//Deletes before insering for simplicity. So you use this for add and edit.
//Note: pass in a negative number
void EditRouteWindowDBC::insertRoute(Route *r, int routeID){
    dropRoute(routeID);
    vector<Route::RoutePoint>::iterator points = r->begin();

    int nextOrder = 1;
    while(points != r->end()){
        this->insertRoutePoint(*points,routeID,nextOrder);
        nextOrder++;
        points++;
    }
}


int EditRouteWindowDBC::getAvailableLocationID(){
    vector<int>* nums = this->getAllLocationIDs();

    for(vector<int>::iterator it = nums->begin(); it != nums->end(); it++){
        cout << *it << ",";
    }

    //if empty ret 1
    if(nums->end() == nums->begin()){
        return 1;
    }

    //else iterate
    vector<int>::iterator it = nums->begin();
    while(it != (nums->end()-1) && *(it+1) == *(it)+1){
        ++it;
    }
    cout <<"available locid " << (*it)+1;
    return (*it)+1;
}


void EditRouteWindowDBC::insertRoutePoint(Route::RoutePoint p,int routeId, int pointOrder){
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(ERWDBCCommands::INSERT_ROUTE_POINT));

    //(routeid,idlocation,numberOfIssues,locationorder) VALUES (:id,:loc,:num,:ord)";
    query->bindValue(":id",routeId);
    query->bindValue(":loc",p.first);
    query->bindValue(":num",p.second);
    query->bindValue(":ord",pointOrder);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(err.isValid()){
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

void EditRouteWindowDBC::dropRoute(int routeID){
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(ERWDBCCommands::DROP_ROUTE));
    query->bindValue(":id",routeID);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(err.isValid()){
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

void EditRouteWindowDBC::dropRouteName(int routeID){
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(ERWDBCCommands::DEL_ROUTENAME));
    query->bindValue(":id",routeID);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(err.isValid())
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;


        return;
}

void EditRouteWindowDBC::addRouteName(int routeID,string name){
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(ERWDBCCommands::ADD_ROUTENAME));
    query->bindValue(":id",routeID);
    query->bindValue(":narm",QString::fromStdString(name));

    client->execute(query);
    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(err.isValid())
        cout << "SQL ERROR: " << result->lastError().text().toStdString() << endl;

    return;
}

void EditRouteWindowDBC::updateRouteName(int routeID,string name){
    dropRouteName(routeID);
    addRouteName(routeID,name);
}
