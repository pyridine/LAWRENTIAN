#include "employeetabledbc.h"
#include <QtSql>
#include <string>
#include <iostream>
#include <qvariant.h>
#include <QTableWidgetItem>

#include "client.h"
namespace ETDBCCommands {
    /*5 (including luid)*/const string GET_REGULAR_EMPLOYEE_DATA = "SELECT luid,name,title,phone,email FROM lawrentian.employee";
    /*6 (including luid)*/const string GET_PRIVILEGED_EMPLOYEE_DATA = "SELECT luid,name,title,phone,email,approved FROM lawrentian.employee";
    /*8 (including luid)*/const string GET_FULL_EMPLOYEE_DATA = "SELECT luid,name,title,phone,email,username,password,approved FROM lawrentian.employee";
    const string GET_NUMBER_OF_EMPLOYEES = "SELECT luid FROM lawrentian.employee";
    const string APPROVE_LUID = "UPDATE lawrentian.employee SET approved=1 WHERE luid=:id";
    const string UNPROVE_LUID = "UPDATE lawrentian.employee SET approved=0 WHERE luid=:id";
    const string GET_NUM_UNREGI = "SELECT luid FROM lawrentian.employee WHERE approved = 0";
}
using namespace ETDBCCommands;
using namespace std;

EmployeeTableDBC::EmployeeTableDBC(Client* c):DatabaseController(c)
{

}

vector<vector<string>>* EmployeeTableDBC::getRegularEmployeeView(){
    int NUMBEROFCOLUMNS = 5;

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(ETDBCCommands::GET_REGULAR_EMPLOYEE_DATA));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<vector<string>>* matrix = new vector<vector<string>>();

    while(result->next()){
        vector<string>* nextRow = new vector<string>();
        for(int i = 0; i < NUMBEROFCOLUMNS; i++){

            switch(i){
            //This needs to be different viz method...
            case 0:
            case 1:
            case 3:
            case 4:
                nextRow->push_back(result->value(i).toString().toStdString());
                break;
            case 2: //translate title int.
                nextRow->push_back(this->translateTitle(result->value(i).toInt()));
                break;
            }
        }
        matrix->push_back(*nextRow);
    }
    return matrix;
}

vector<vector<string>>* EmployeeTableDBC::getPrivilegedEmployeeView(){
    int NUMBEROFCOLUMNS = 6;

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(ETDBCCommands::GET_PRIVILEGED_EMPLOYEE_DATA));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<vector<string>>* matrix = new vector<vector<string>>();

    while(result->next()){
        vector<string>* nextRow = new vector<string>();
        for(int i = 0; i < NUMBEROFCOLUMNS; i++){

            switch(i){
            //This needs to be different viz method...
            case 0:
            case 1:
            case 3:
            case 4:
                nextRow->push_back(result->value(i).toString().toStdString());
                break;
            case 2: //translate title int.
                nextRow->push_back(this->translateTitle(result->value(i).toInt()));
                break;
            case 5:
                int val = result->value(i).toInt();
                if(val == 1){
                    nextRow->push_back("yes");
                } else{
                    nextRow->push_back("no");
                }
                break;
            }
        }
        matrix->push_back(*nextRow);
    }

    return matrix;
}

vector<vector<string>>* EmployeeTableDBC::getFullEmployeeView(){
    int NUMBEROFCOLUMNS = 8;

    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(ETDBCCommands::GET_FULL_EMPLOYEE_DATA));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    vector<vector<string>>* matrix = new vector<vector<string>>();

    while(result->next()){
        vector<string>* nextRow = new vector<string>();
        for(int i = 0; i < NUMBEROFCOLUMNS; i++){

            switch(i){
            //This needs to be different viz method...
            case 0:
            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
                nextRow->push_back(result->value(i).toString().toStdString());
                break;
            case 2: //translate title int.
                nextRow->push_back(this->translateTitle(result->value(i).toInt()));
                break;
            case 7:
                int val = result->value(i).toInt();
                if(val == 1){
                    nextRow->push_back("yes");
                } else{
                    nextRow->push_back("no");
                }
                break;

            }
        }
        matrix->push_back(*nextRow);
    }

    return matrix;
}

int EmployeeTableDBC::getNumberOfEmployees(){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(ETDBCCommands::GET_NUMBER_OF_EMPLOYEES));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    int numEmployees = 0;

    if(!err.isValid()){
        while(result->next()){
            ++numEmployees;
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return numEmployees;
}

void EmployeeTableDBC::unnaproveEmployee(int luid){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(ETDBCCommands::UNPROVE_LUID));
    query->bindValue(":id",luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        return;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

void EmployeeTableDBC::approveEmployee(int luid){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(ETDBCCommands::APPROVE_LUID));
    query->bindValue(":id",luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        return;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }

}

int EmployeeTableDBC::getNumUnregistered(){
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(ETDBCCommands::GET_NUM_UNREGI));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    int NoMatterHowILookAtItItsYouGuysFaultImNotPopular = 0;

    if(!err.isValid()){     
        while(result->next()){
            ++NoMatterHowILookAtItItsYouGuysFaultImNotPopular;
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return NoMatterHowILookAtItItsYouGuysFaultImNotPopular;

}

EmployeeTableDBC::~EmployeeTableDBC()
{

}

