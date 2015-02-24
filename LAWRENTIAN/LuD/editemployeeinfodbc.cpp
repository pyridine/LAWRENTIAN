#include "editemployeeinfodbc.h"
#include <QtSql>
#include <qvariant.h>
#include <iostream>

EditEmployeeInfoDBC::EditEmployeeInfoDBC(Client *c):DatabaseController(c)
{

}

vector<string> EditEmployeeInfoDBC::collectRegisteredNames(){
    const string GET_REGISTERED_NAMES = "SELECT name, username FROM lawrentian.employee ORDER BY name ASC";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_REGISTERED_NAMES));

    vector<string> namesList;

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            string name = result->value(0).toString().toStdString();
            //string username = result->value(1).toString().toStdString();
            //string concatName = name+", "+username;
            namesList.push_back(name);
        }
        return namesList;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

int EditEmployeeInfoDBC::collectLuid(string username)
{
    const string GET_LUID = "SELECT luid FROM lawrentian.employee WHERE name =:name";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_LUID));
    query->bindValue(":name", QString::fromStdString(username));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    int luidInt;

    if(!err.isValid()){
        while(result->next()){
            string luid = result->value(0).toString().toStdString();
            luidInt = stoi(luid);
        }
        return luidInt;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

string EditEmployeeInfoDBC::collectTitle(string username)
{
    const string GET_TITLE = "SELECT lawrentian.titledefinitions.titleName "
                            "FROM lawrentian.titledefinitions "
                            "INNER JOIN lawrentian.employee "
                            "ON lawrentian.titledefinitions.idTitle = lawrentian.employee.title "
                            "WHERE lawrentian.employee.name = :name";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_TITLE));
    query->bindValue(":name", QString::fromStdString(username));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    string title;

    if(!err.isValid()){
        while(result->next()){
            title = result->value(0).toString().toStdString();
        }
        return title;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

string EditEmployeeInfoDBC::collectEmail(string username)
{
    const string GET_EMAIL = "SELECT email FROM lawrentian.employee WHERE name =:name";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_EMAIL));
    query->bindValue(":name", QString::fromStdString(username));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    string email;

    if(!err.isValid()){
        while(result->next()){
            email = result->value(0).toString().toStdString();
        }
        return email;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

string EditEmployeeInfoDBC::collectPhone(string username)
{
    const string GET_PHONE = "SELECT phone FROM lawrentian.employee WHERE name =:name";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_PHONE));
    query->bindValue(":name", QString::fromStdString(username));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    string phone;

    if(!err.isValid()){
        while(result->next()){
            phone = result->value(0).toString().toStdString();
        }
        return phone;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

int EditEmployeeInfoDBC::collectApproved(string username)
{
    const string GET_APPROVED = "SELECT approved FROM lawrentian.employee WHERE name =:name";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_APPROVED));
    query->bindValue(":name", QString::fromStdString(username));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    int approvedInt;

    if(!err.isValid()){
        while(result->next()){
            string approved = result->value(0).toString().toStdString();
            approvedInt = stoi(approved);
        }
        return approvedInt;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

void EditEmployeeInfoDBC::saveEmployeeChanges(string oldName, string newName, int luid, string title, string email, string phone, int approved)
{
    const string GET_TITLE_NAME = "SELECT idTitle FROM lawrentian.titledefinitions WHERE titleName =:title";
    QSqlQuery* query1 = new QSqlQuery();
    query1->prepare(QString::fromStdString(GET_TITLE_NAME));
    query1->bindValue(":title", QString::fromStdString(title));

    QSqlQuery* result1 = client->execute(query1);
    QSqlError err1 = result1->lastError();

    int titleInt;

    if(!err1.isValid()){
        while(result1->next()){
            titleInt = result1->value(0).toInt();
        }
    }else{
        cout << "!SQL ERROR: " << result1->lastError().text().toStdString() << endl;
    }

    cout<<"Computed realTitle: "<<titleInt<<endl;
    cout<<"Old Name: "<<oldName<<endl;
    cout<<"New Name: "<<newName<<endl;
    cout<<"LUID: "<<luid<<endl;
    cout<<"Title: "<<title<<endl;
    cout<<"Email: "<<email<<endl;
    cout<<"Phone: "<<phone<<endl;
    cout<<"Approved: "<<approved<<endl;

    const string SAVE_EMPLOYEE_INFO = "UPDATE lawrentian.employee "
                                      "SET luid=:luid, name=:newName, title=:title, email=:email, phone=:phone, approved=:approved "
                                      "WHERE lawrentian.employee.luid=:luid";
    QSqlQuery* query2 = new QSqlQuery();
    query2->prepare(QString::fromStdString(SAVE_EMPLOYEE_INFO));
    query2->bindValue(":luid", luid);
    query2->bindValue(":newName", QString::fromStdString(newName));
    query2->bindValue(":oldName", QString::fromStdString(oldName));
    query2->bindValue(":title", titleInt);
    query2->bindValue(":email", QString::fromStdString(email));
    query2->bindValue(":phone", QString::fromStdString(phone));
    query2->bindValue(":approved", approved);

    QSqlQuery* result2 = client->execute(query2);
    QSqlError err2 = result2->lastError();

    if(!err2.isValid()){
        return;
    }else{
        cout << "!SQL ERROR: " << result2->lastError().text().toStdString() << endl;
    }
}

EditEmployeeInfoDBC::~EditEmployeeInfoDBC()
{

}

