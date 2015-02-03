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
    /*checked*/QString name = ui->nameTextField->text();
    /*checked*/string stringName = name.toStdString();

    /*not checked*/QString luId = ui->luIdTextField->text();
    /*not checked*/string stringLuId = luId.toStdString();

    /*not checked*/QString email = ui->emailTextField->text();
    /*not checked*/string stringEmail = email.toStdString();

    /*checked*/QString phone = ui->phoneTextField->text();
    /*checked*/string stringPhone = phone.toStdString();

    /*checked*/QString username = ui->usernameTextField->text();
    /*checked*/string stringUsername = username.toStdString();

    /*checked*/QString password = ui->passwordTextField->text();
    /*checked*/string stringPassword = password.toStdString();

    /*checked*/QString confirmPassword = ui->confirmPasswordTextField->text();
    /*checked*/string stringConfirmPassword = password.toStdString();

    //Let's be consistent and only work with either the QStrings or the strings.

    bool fieldsAreSatisfied = true;

    //Check to see if any field is empty (one if statement why not!)
    if(stringName.begin() == stringName.end()
            || stringLuId.begin() == stringLuId.end()
            || stringEmail.begin() == stringEmail.end()
            || stringPhone.begin() == stringPhone.end()
            || stringUsername.begin() == stringUsername.end())
    {
        RegistrationWindow::showAlert("Error", "A field is blank, numbnuts!");
        fieldsAreSatisfied = false;

    }

    //Check to see if the phone number field is *probably* a phone number :P
    if(!RegistrationWindow::isPhoneNumberDubiouslyValid(stringPhone)){
        RegistrationWindow::showAlert("Error", "Your phone number's invalid, you fool!");
        fieldsAreSatisfied = false;
    }

    //Check to see if the email field is in fact an email
    if(!RegistrationWindow::isEmailValid(stringEmail)){
        RegistrationWindow::showAlert("Error", "Your email is invalid! What's wrong with you??");
        fieldsAreSatisfied = false;
    }

    //Check to see if passwords match.
    if(stringPassword != stringConfirmPassword){
        RegistrationWindow::showAlert("Error", "Your passwords don't match, moron!");
        fieldsAreSatisfied = false;
    }
    //Check to see if password conforms to standards.
    if(!RegistrationWindow::isPasswordSuitable(stringPassword)){
        RegistrationWindow::showAlert("Error", "Password must contain at least one number (0-9), one upper case character (A-Z), and one lower case character (a-z). You idiot.");
        fieldsAreSatisfied = false;
    }

    //Check if LU ID is probably an ID.
    if(!RegistrationWindow::isLuIDDubiouslyValid(stringLuId)){
        RegistrationWindow::showAlert("Error", "Your LU ID appears to be invalid. We only need the number. Go back to grade school!");
        fieldsAreSatisfied = false;
    }

    if(fieldsAreSatisfied){
        Employee employee(stringName, stringLuId, stringEmail, stringPhone, stringUsername, stringPassword);
        employeeVector.push_back(employee);
        cout<<employee.getName()<<endl;
        cout<<employee.getLuId()<<endl;
        cout<<employee.getEmail()<<endl;
        cout<<employee.getPhoneNumber()<<endl;
        cout<<employee.getUsername()<<endl;
        cout<<employee.getPassword()<<endl;
    }
}

bool RegistrationWindow::isPasswordSuitable(string s)
{
    string::iterator itr;
    bool containsNum = false;
    bool containsLow = false;
    bool containsUp = false;

    if(s.begin() == s.end()){
        cout << "empty password" << endl;
        return false;
    }

    for(itr = s.begin(); itr < s.end(); itr++){
        if(islower(*itr)){
            containsLow = true;
        }
        if(isupper(*itr)){
            containsUp = true;
        }
        if(!isdigit(*itr)){
            containsNum = true;
        }
    }

    return (containsNum && containsLow && containsUp);
}

void RegistrationWindow::showAlert(const string& title,const string& msg){
    QMessageBox alertBox;
    QString t = QString::fromUtf8(title.c_str());
    QString m = QString::fromUtf8(msg.c_str());
    alertBox.critical(0, t,m);
    alertBox.setFixedSize(500,200);
}

bool RegistrationWindow::isLuIDDubiouslyValid(std::string inputID){

    string::iterator itr;
    int numberOfNumbers = 0;
    for(itr = inputID.begin(); itr < inputID.end(); itr++){
        if(!isdigit(*itr)){
            return false;
        }
    }
    return true;
}

bool RegistrationWindow::isPhoneNumberDubiouslyValid(std::string inputPhone)
{
    string::iterator itr;
    int numberOfNumbers = 0;
    for(itr = inputPhone.begin(); itr < inputPhone.end(); itr++){
        if(isdigit(*itr)){
            ++numberOfNumbers;
        }
    }
    return(numberOfNumbers == 10);
}

bool RegistrationWindow::isEmailValid(std::string sbemail){
    string::iterator itr;
    /*
    1•The email address must start with a letter (no numbers or symbols)
    2•There must be an @ somewhere in the string that is located BEFORE the dot
    3•There must be text after the @ symbol but BEFORE the dot
    4•There must be a dot
    5•There must be text after the dot
    */

    itr = sbemail.begin();

    //1
    if(!isalpha(*itr)){
       return false;
    }
    ++itr;
    //2
    while(itr != sbemail.end() && isalnum(*itr)){
        ++itr;
    }
    if(itr == sbemail.end() || *itr != '@'){
        return false;
    }
    ++itr;
    //3
    if(!isalpha(*itr)){
        return false;
    }
    //4
    while(itr != sbemail.end() && isalnum(*itr)){
        ++itr;
    }
    if(itr == sbemail.end() || *itr != '.'){
        return false;
    }
    ++itr;
    //5
    while(itr != sbemail.end()){
        if(!isalpha(*itr)){
            return false;
        }
        ++itr;
    }
    return true;
}