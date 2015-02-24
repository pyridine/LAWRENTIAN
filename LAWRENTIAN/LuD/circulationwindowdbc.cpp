#include "circulationwindowdbc.h"
#include "route.h"
#include <iostream>
#include <qvariant.h>
#include <QTableWidgetItem>
#include <QtSql>
#include <utility>
#include <QtSql/qsqlerror.h>

namespace CWDBCCommands {
    const string GET_ALL_ROUTE_NUMS = "SELECT routeid FROM lawrentian.routes";
    const string GET_ROUTE_POINTS = "SELECT idlocation,numberOfIssues FROM lawrentian.routes WHERE routeid = :id ORDER BY locationorder ASC";
    const string DROP_ROUTE = "DELETE FROM lawrentian.routes WHERE routeid = :id";
    const string INSERT_ROUTE_POINT = "INSERT INTO lawrentian.routes (routeid,idlocation,numberOfIssues,locationorder) VALUES (:id,:loc,:num,:ord)";
}
using namespace CWDBCCommands;
using namespace std;

CirculationWindowDBC::CirculationWindowDBC(Client* c):DatabaseController(c)
{

}

CirculationWindowDBC::~CirculationWindowDBC()
{

}

vector<pair<Route*,int>*>* CirculationWindowDBC::getAllRoutes(){
    vector<int>* routeNumbers = this->getAllRouteNums();
    vector<pair<Route*,int>*>* routes = new vector<pair<Route*,int>*>;

    vector<int>::iterator nextRouteNum = routeNumbers->begin();

    while(nextRouteNum != routeNumbers->begin()){
        Route* nextRoute = this->getRoute(*nextRouteNum);
        routes->push_back(new pair<Route*,int>(nextRoute,*nextRouteNum));
    }

    return routes;
}



Route* CirculationWindowDBC::getRoute(int routeId){


    //"SELECT idlocation,numberOfIssues FROM lawrentian.routes WHERE routeid = :id ORDER BY locationorder ASC";

    Route* newRoute = new Route();
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(CWDBCCommands::GET_ROUTE_POINTS));
    query->bindValue(":id",routeId);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            int nextLocId = result->value(0).toInt();
            int nextNumIss = result->value(1).toInt();
            Route::RoutePoint* nextPoint = new pair<int,int>(nextLocId,nextNumIss);
            newRoute->addNode(nextPoint,newRoute->end());
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return newRoute;
}


//Deletes before insering for simplicity. So you use this for add and edit.
//Note: pass in a negative number
void CirculationWindowDBC::insertRoute(Route *r, int routeID){
    dropRoute(routeID);
    vector<Route::RoutePoint>::iterator points = r->begin();

    int nextOrder = 1;
    while(points != r->end()){
        this->insertRoutePoint(*points,routeID,nextOrder);
        nextOrder++;
    }
}



void CirculationWindowDBC::dropRoute(int routeID){
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(CWDBCCommands::DROP_ROUTE));
    query->bindValue(":id",routeID);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(err.isValid()){
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

int CirculationWindowDBC::getAvailableRouteId(){ //Really important for inserting
    return findMissingNumber(getAllRouteNums());
}
vector<int>* CirculationWindowDBC::getAllRouteNums(){
    vector<int>* numz = new vector<int>();
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(CWDBCCommands::GET_ALL_ROUTE_NUMS));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){

        while(result->next()){
            numz->push_back(result->value(0).toInt());
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return numz;
}

void CirculationWindowDBC::insertRoutePoint(Route::RoutePoint p,int routeId, int pointOrder){
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(CWDBCCommands::INSERT_ROUTE_POINT));

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

/**
  returns the first number missing in v.
  !!v must be sorted in ascending order.!!
 * @brief findMissingNumber
 * @param v
 */
int CirculationWindowDBC::findMissingNumber(vector<int>* v){
    //cout v for testing
    for(vector<int>::iterator it = v->begin(); it != v->end(); it++){
        cout << *it << ",";
    }
    cout << endl;

    //if empty ret 1
    if(v->end() == v->begin()){
        return 1;
    }

    //else iterate
    vector<int>::iterator it = v->begin();
    int nextInt = *it;
    ++it;
    while(it != v->end() && *(it+1) == nextInt+1){ //TODO: TESTING: I'M NOT SURE THAT *(it+1) WORKS
        ++it;
        nextInt = *it;
    }
    return nextInt+1;
}
