#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "employee.h"

#include <iostream>
#include <QDebug>

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

    Employee employee(stringName, stringLuId, stringEmail, stringPhone, stringUsername, stringPassword);
    employeeVector.push_back(employee);
    cout<<employee.getName()<<endl;
    cout<<employee.getLuId()<<endl;
    cout<<employee.getEmail()<<endl;
    cout<<employee.getPhoneNumber()<<endl;
    cout<<employee.getUsername()<<endl;
    cout<<employee.getPassword()<<endl;
}
