#include "circulationwindowdbc.h"
#include "route.h"
#include <iostream>
#include <qvariant.h>
#include <QTableWidgetItem>
#include <QtSql>
#include <utility>
#include <QtSql/qsqlerror.h>

namespace CWDBCCommands {
    const string GET_ALL_NUM_ISSUES = "SELECT numberOfIssues FROM lawrentian.routes";
    const string GET_ALL_ROUTE_NUMS = "SELECT routeid FROM lawrentian.routes GROUP BY routeid";
    const string GET_ROUTE_POINTS = "SELECT idlocation,numberOfIssues FROM lawrentian.routes WHERE routeid = :id ORDER BY locationorder ASC";
}
using namespace CWDBCCommands;
using namespace std;

CirculationWindowDBC::CirculationWindowDBC(Client* c):DatabaseController(c)
{

}

CirculationWindowDBC::~CirculationWindowDBC()
{

}

vector<pair<Route*,int>>* CirculationWindowDBC::getAllRoutes(){
    vector<int>* routeNumbers = this->getAllRouteNums();
    vector<pair<Route*,int>>* routes = new vector<pair<Route*,int>>;

    vector<int>::iterator nextRouteNum = routeNumbers->begin();

    while(nextRouteNum != routeNumbers->end()){
        Route* nextRoute = this->getRoute(*nextRouteNum);
        pair<Route*,int>* nextRP = new pair<Route*,int>(nextRoute,*nextRouteNum);
        routes->push_back(*nextRP);
        nextRouteNum++;
    }

    return routes;
}



Route* CirculationWindowDBC::getRoute(int routeId){


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
            newRoute->insert(nextPoint,newRoute->end());
        }
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return newRoute;
}

int CirculationWindowDBC::sumTotalCopies(){
    int num = 0;
    QSqlQuery* query = new QSqlQuery();

    query->prepare(QString::fromStdString(CWDBCCommands::GET_ALL_NUM_ISSUES));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){

        while(result->next()){
            num += result->value(0).toInt();
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return num;
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

/**
  returns the first number missing in v.
  !!v must be sorted in ascending order.!!
 * @brief findMissingNumber
 * @param v
 */
int CirculationWindowDBC::findMissingNumber(vector<int>* nums){

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
    return (*it)+1;
}
