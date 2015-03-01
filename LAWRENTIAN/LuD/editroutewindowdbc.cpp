#include "editroutewindowdbc.h"
#include <utility>
#include <iostream>
#include "route.h"

using std::vector;
using std::string;
using namespace std;
namespace ERWDBCCommands{
     const string GETALLLOCNUMS = "SELECT idlocation from lawrentian.location";
     const string DROP_ROUTE = "DELETE FROM lawrentian.routes WHERE routeid = :id";
     const string INSERT_ROUTE_POINT = "INSERT INTO lawrentian.routes (routeid,idlocation,numberOfIssues,locationorder) VALUES (:id,:loc,:num,:ord)";
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
