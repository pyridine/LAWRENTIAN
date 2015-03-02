#include "addlocationwindowdbc.h"
#include <iostream>
using namespace std;

AddLocationWindowDBC::AddLocationWindowDBC(Client* c):DatabaseController(c)
{

}

AddLocationWindowDBC::~AddLocationWindowDBC()
{

}

void AddLocationWindowDBC::dropLocation(int locID){
    QSqlQuery* query = new QSqlQuery();

    query->prepare("DELETE FROM lawrentian.location WHERE idlocation = :id");
    query->bindValue(":id",locID);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid())cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    return;
}

void AddLocationWindowDBC::addLocation(int locID, string loc){
    QSqlQuery* query = new QSqlQuery();

    query->prepare("INSERT INTO lawrentian.location (idlocation,name) VALUES (:locId,:loc)");
    query->bindValue(":locId",locID);
    query->bindValue(":loc",QString::fromStdString(loc));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid())cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    return;

}
