#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "employee.h"

#include <iostream>
#include <QDebug>
#include <QMessageBox>
#include <ctype.h>
#include <stdio.h>

using namespace std;

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_submitButton_clicked()
{
    QString name = ui->nameTextField->text();
    string stringName = name.toStdString();
    QString luId = ui->luIdTextField->text();
    string stringLuId = luId.toStdString();
    QString email = ui->emailTextField->text();
    string stringEmail = email.toStdString();
    QString phone = ui->phoneTextField->text();
    string stringPhone = phone.toStdString();
    QString username = ui->usernameTextField->text();
    string stringUsername = username.toStdString();
    QString password = ui->passwordTextField->text();
    string stringPassword = password.toStdString();
    QString confirmPassword = ui->confirmPasswordTextField->text();
    string stringConfirmPassword;


    bool fieldsAreSatisfied = true;

    if(password != confirmPassword){
        QMessageBox alertBox;
        alertBox.critical(0, "Error", "Confirm password does not match");
        alertBox.setFixedSize(500,200);
        fieldsAreSatisfied = false;
    }
    if(!RegistrationWindow::isPasswordSuitable(password.toStdString())){
        QMessageBox alertBox;
        alertBox.critical(0, "Error", "Password must contain at least one number (0-9), one upper case character (A-Z), and one lower case character (a-z).");
        alertBox.setFixedSize(500,200);
        fieldsAreSatisfied = false;
    }




    Employee employee(stringName, stringLuId, stringEmail, stringPhone, stringUsername, stringPassword);
    employeeVector.push_back(employee);
    cout<<employee.getName()<<endl;
    cout<<employee.getLuId()<<endl;
    cout<<employee.getEmail()<<endl;
    cout<<employee.getPhoneNumber()<<endl;
    cout<<employee.getUsername()<<endl;
    cout<<employee.getPassword()<<endl;
}

bool RegistrationWindow::isPasswordSuitable(string s)
{
    string::iterator itr;
    bool containsNum = false;
    bool containsLow = false;
    bool containsUp = false;

    if(s.begin() == s.end()){
        return false;
    }

    for(itr = s.begin(); itr < s.end(); itr++){
        if(islower(*itr)){
            containsLow = true;
        }
        if(isupper(*itr)){
            containsUp = true;
        }
        if(!isalpha(*itr)){
            containsNum = true;
        }
    }

    return (containsNum && containsLow && containsUp);
}
