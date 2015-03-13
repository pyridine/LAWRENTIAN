#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "employee.h"
#include "checkemployeeswindow.h"

#include <iostream>
#include <QDebug>
#include <QMessageBox>
#include "client.h"
#include "registrationwindowdbcontroller.h"
#include <string>
#include <iostream>

using namespace std;

RegistrationWindow::RegistrationWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::RegistrationWindow)
{
    std::cout << "Hi, I am REGISTRATIONWINDOW." << endl;
    ui->setupUi(this);
    ui->passwordErrorLabel->setText("Password not suitable");
    ui->passwordErrorLabel->hide();


    RegistrationWindowDBController rwdbc;
    RegistrationWindow::dbController = &rwdbc;
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::initDB(Client* cp){

    RegistrationWindow::dbController->init(cp);
}

void RegistrationWindow::on_submitButton_clicked()
{
    /*checked*/QString name = ui->nameTextField->text();
    /*checked*/string stringName = name.toStdString();

    /*checked*/QString luId = ui->luIdTextField->text();
    /*checked*/string stringLuId = luId.toStdString();

    /*checked*/QString email = ui->emailTextField->text();
    /*checked*/string stringEmail = email.toStdString();

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

    //Check to see if the name field is *probably* a name :P
    if(!RegistrationWindow::isValidUsername(stringName)){
        RegistrationWindow::showAlert("Error", "Name invalid.");
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
    if(stringPassword.compare(stringConfirmPassword) != 0){
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
        Employee employee(stringName, std::stoi(stringLuId) /*string to int. If this gives problems, make sure you're using c++11 (see the config section of the .pro file)*/,
                          stringEmail, "NONE", stringPhone, stringUsername, stringPassword, 0);



        RegistrationWindow::dbController->addEmployee(&employee);

        /*employeeVector.push_back(employee);*/
        ui->nameTextField->setText("");
        ui->luIdTextField->setText("");
        ui->emailTextField->setText("");
        ui->phoneTextField->setText("");
        ui->usernameTextField->setText("");
        ui->passwordTextField->setText("");
        ui->confirmPasswordTextField->setText("");
        ui->passwordErrorLabel->hide();

        RegistrationWindow::showAlert("Registration complete","Thank you for registering.\n The Employee Manager must approve your registration before you are able to log in.");
        RegistrationWindow::hide();
    }
}

bool RegistrationWindow::isPasswordSuitable(string s){
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



void RegistrationWindow::on_pushButton_clicked()
{
    if(employeeVector.size() > 0){
    checkEmployeesWindow = new CheckEmployeesWindow;
    checkEmployeesWindow->initCheckEmployeesWindow(employeeVector); // Passes in the employee vector
    checkEmployeesWindow->show();
    }else {
        RegistrationWindow::showAlert("Error", "No employees available");
    }
}

void RegistrationWindow::showAlert(const string& title,const string& msg)
{
    QMessageBox alertBox;
    QString t = QString::fromUtf8(title.c_str());
    QString m = QString::fromUtf8(msg.c_str());
    alertBox.critical(0, t,m);
    alertBox.setFixedSize(500,200);
}

bool RegistrationWindow::isValidUsername(std::string s) {return s.size() != 0 && s.find(' ') != 0 && s.rfind(' ') != s.size() - 1  ? true : false; }

bool RegistrationWindow::isLuIDDubiouslyValid(std::string inputID){

    string::iterator itr;
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
    return(numberOfNumbers >= 1);
}

bool RegistrationWindow::isEmailValid(std::string sbemail){
    string::iterator itr;
    /*
    1•The email address must start with a letter (no numbers or symbols)
    2•There must be an @ somewhere in the string that is located before the domain dot
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
    while((itr != sbemail.end() && isalnum(*itr)) || *itr == '.'){
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

void RegistrationWindow::on_passwordTextField_textChanged(const QString &arg1)
{
    if(RegistrationWindow::isPasswordSuitable(ui->passwordTextField->text().toStdString())){
        ui->passwordErrorLabel->hide();
    }else{
        ui->passwordErrorLabel->show();
    }
}
