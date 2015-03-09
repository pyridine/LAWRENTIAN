#include "editprofiledbc.h"
#include <QtSql>
#include <qvariant.h>
#include <iostream>

EditProfileDBC::EditProfileDBC(Client *c):DatabaseController(c)
{

}

string EditProfileDBC::collectName(int luid){
    const string GET_NAME = "SELECT name FROM lawrentian.employee WHERE luid =:luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_NAME));
    query->bindValue(":luid", luid);

    string name;

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        while(result->next()){
            name = result->value(0).toString().toStdString();
        }
        return name;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return NULL;
    }
}

int EditProfileDBC::collectLuid(int luid)
{
    const string GET_LUID = "SELECT luid FROM lawrentian.employee WHERE luid =:luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_LUID));
    query->bindValue(":luid", luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    int luidInt;

    if(!err.isValid()){
        while(result->next()){
            string luid = result->value(0).toString().toStdString();
            luidInt = stoi(luid);
        }

    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
    return luidInt;
}

string EditProfileDBC::collectTitle(int luid)
{
    const string GET_TITLE = "SELECT lawrentian.titledefinitions.titleName "
                            "FROM lawrentian.titledefinitions "
                            "INNER JOIN lawrentian.employee "
                            "ON lawrentian.titledefinitions.idTitle = lawrentian.employee.title "
                            "WHERE lawrentian.employee.luid = :luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_TITLE));
    query->bindValue(":luid", luid);

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
        return NULL;
    }
}

string EditProfileDBC::collectEmail(int luid)
{
    const string GET_EMAIL = "SELECT email FROM lawrentian.employee WHERE luid =:luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_EMAIL));
    query->bindValue(":luid", luid);

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
        return NULL;
    }
}

string EditProfileDBC::collectPhone(int luid)
{
    const string GET_PHONE = "SELECT phone FROM lawrentian.employee WHERE luid =:luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_PHONE));
    query->bindValue(":luid", luid);

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
        return NULL;
    }
}

string EditProfileDBC::collectUsername(int luid)
{
    const string GET_USERNAME = "SELECT username FROM lawrentian.employee WHERE luid =:luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_USERNAME));
    query->bindValue(":luid", luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    string username;

    if(!err.isValid()){
        while(result->next()){
            username = result->value(0).toString().toStdString();
        }
        return username;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return NULL;
    }
}

string EditProfileDBC::collectOldPassword(int luid)
{
    const string GET_PASSWORD = "SELECT password FROM lawrentian.employee WHERE luid =:luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(GET_PASSWORD));
    query->bindValue(":luid", luid);

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    string password;

    if(!err.isValid()){
        while(result->next()){
            password = result->value(0).toString().toStdString();
        }
        return password;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
        return NULL;
    }
}

void EditProfileDBC::saveEmployeeChangesWithPassword(string name, string email, string phone, string username, string newPassword, int luid)
{
    const string SAVE_EMPLOYEE_INFO = "UPDATE lawrentian.employee "
                                      "SET name=:newName, email=:email, phone=:phone, username=:username, password=:newPassword "
                                      "WHERE lawrentian.employee.luid=:luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(SAVE_EMPLOYEE_INFO));
    query->bindValue(":luid", luid);
    query->bindValue(":newName", QString::fromStdString(name));
    query->bindValue(":email", QString::fromStdString(email));
    query->bindValue(":phone", QString::fromStdString(phone));
    query->bindValue(":username", QString::fromStdString(username));
    query->bindValue(":newPassword", QString::fromStdString(newPassword));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        return;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

void EditProfileDBC::saveEmployeeChangesWithoutPassword(string name, string email, string phone, string username, int luid)
{
    const string SAVE_EMPLOYEE_INFO = "UPDATE lawrentian.employee "
                                      "SET name=:newName, email=:email, phone=:phone, username=:username "
                                      "WHERE lawrentian.employee.luid=:luid";
    QSqlQuery* query = new QSqlQuery();
    query->prepare(QString::fromStdString(SAVE_EMPLOYEE_INFO));
    query->bindValue(":luid", luid);
    query->bindValue(":newName", QString::fromStdString(name));
    query->bindValue(":email", QString::fromStdString(email));
    query->bindValue(":phone", QString::fromStdString(phone));
    query->bindValue(":username", QString::fromStdString(username));

    QSqlQuery* result = client->execute(query);
    QSqlError err = result->lastError();

    if(!err.isValid()){
        return;
    }else{
        cout << "!SQL ERROR: " << result->lastError().text().toStdString() << endl;
    }
}

EditProfileDBC::~EditProfileDBC()
{

}

